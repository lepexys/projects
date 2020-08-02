#include "deliveries.h"
#include "ui_deliveries.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QSqlRecord>


deliveries::deliveries(QWidget *parent,QSqlDatabase *db) : QWidget(parent)
  ,ui(new Ui::deliveries)
{
    ui->setupUi(this);
    mdl = new QSqlTableModel(this,*db);
    mdl->setTable("purchase");
    mdl->select();
    mdl->setHeaderData(0,Qt::Horizontal,"№");
    mdl->setHeaderData(1,Qt::Horizontal,"№ Продукта");
    mdl->setHeaderData(2,Qt::Horizontal,"№ Поставщика");
    mdl->setHeaderData(3,Qt::Horizontal,"Дата");
    mdl->setHeaderData(4,Qt::Horizontal,"Цена за единицу");
    mdl->setHeaderData(5,Qt::Horizontal,"Количество");
    mdl->setHeaderData(6,Qt::Horizontal,"Сумма НДС");
    mdl->setHeaderData(7,Qt::Horizontal,"№ Склада");
    mdl->setHeaderData(8,Qt::Horizontal,"№ Договора");
    mdl->setHeaderData(9,Qt::Horizontal,"Единицы");
    mdl->setHeaderData(10,Qt::Horizontal,"№ Заказа");
    ui->tableView->setModel(mdl);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() + ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2) + ui->tableView->columnWidth(3)
                  + ui->tableView->columnWidth(4)+ ui->tableView->columnWidth(5)+ ui->tableView->columnWidth(6)+ ui->tableView->columnWidth(7)+ ui->tableView->columnWidth(8)
                  + ui->tableView->columnWidth(9)+ ui->tableView->columnWidth(10)+ ui->tableView->columnWidth(11));
    ui->tableView->setGeometry(rect);
}

void deliveries::on_pushButton_Add_clicked()
{
    if(!ui->lineEdit_4->text().isEmpty() && !ui->lineEdit_6->text().isEmpty() && !ui->lineEdit_7->text().isEmpty() && !ui->lineEdit_2->text().isEmpty() && !ui->lineEdit_9->text().isEmpty()
            && !ui->lineEdit_10->text().isEmpty() && !ui->lineEdit_5->text().isEmpty())
    {
        QSqlQuery query(mdl->database());
        query.prepare(QString("INSERT INTO purchase (product_id, dealer_id, date, price_per_unit, amount, vat_sum, storage, contract, unit, order_id) "
                              "VALUES (:product_id, :dealer_id, :date, :price_per_unit, :amount, :vat_sum, :storage, :contract, :unit, :order_id)"));
        query.bindValue(":product_id",ui->lineEdit_4->text());
        query.bindValue(":dealer_id",ui->lineEdit_6->text());
        query.bindValue(":date",QDate::currentDate().toString(Qt::ISODate));
        query.bindValue(":price_per_unit",QString::number(ui->lineEdit_7->text().toDouble(),'f',2));
        query.bindValue(":amount",QString::number(ui->lineEdit_2->text().toDouble(),'f',2));
        query.bindValue(":vat_sum",(ui->doubleSpinBox->text().toDouble() == 0.00)?QString("0.13"):QString::number(ui->doubleSpinBox->text().toDouble(),'f',2));
        query.bindValue(":storage",ui->lineEdit_9->text());
        query.bindValue(":contract",ui->lineEdit_10->text());
        QSqlQuery query1(mdl->database());
        query1.exec("SELECT * FROM goods WHERE id = "+QString(ui->lineEdit_4->text()));
        if(query1.next())
        {
            query.bindValue(":unit",query1.value(query1.record().indexOf("units")).toString().isEmpty()?QString("шт."):query1.value(query1.record().indexOf("units")).toString());
        }
        QString unit = query1.value(query1.record().indexOf("units")).toString().isEmpty()?QString("шт."):query1.value(query1.record().indexOf("units")).toString();
        query.bindValue(":order_id",ui->lineEdit_5->text());
        if(!query.exec())
            QMessageBox::critical(NULL,QObject::tr("Ошибка"),query.lastError().text());
        else
        {
            QString sum = QString::number(ui->lineEdit_2->text().toDouble()*ui->lineEdit_7->text().toDouble(),'f',2);
            QSqlQuery query2(mdl->database());
            QSqlQuery query3(mdl->database());
            query2.exec("SELECT * FROM bill WHERE order_id = "+QString(ui->lineEdit_5->text()));
            QString nds = (ui->doubleSpinBox->text().toDouble() == 0.00)?QString("0.87"):QString::number(1.0 - ui->doubleSpinBox->text().toDouble(),'f',2);
            if(query2.next())
            {
                query3.exec("UPDATE bill SET sum = "+ sum +" * "+nds+" + sum WHERE order_id = "+ui->lineEdit_5->text());
            }
            else
            {
                if(!query3.exec("INSERT INTO bill (order_id, sum, discount) VALUES ("+ui->lineEdit_5->text()+", "+ QString::number(sum.toDouble() * nds.toDouble(),'f',2)+", "+QString::number(0.00,'f',2)+")"))
                    QMessageBox::critical(NULL,QObject::tr("Ошибка"),query3.lastError().text());
            }
            QSqlQuery query4(mdl->database());
            QSqlQuery query5(mdl->database());
            query4.exec("SELECT * FROM storage WHERE product_id = "+ui->lineEdit_4->text()+" AND code = "+QString(ui->lineEdit_9->text()));
            if(query4.next())
            {
                query5.exec("UPDATE storage SET amount = "+QString::number(ui->lineEdit_2->text().toFloat(),'f',2)+" + amount WHERE product_id = "+ui->lineEdit_4->text()+" AND code = "+QString(ui->lineEdit_9->text()));
            }
            else
            {
                if(!query5.exec("INSERT INTO storage (product_id, amount, units, code) "
                            "VALUES ("+ui->lineEdit_4->text()+", "+QString::number(ui->lineEdit_2->text().toFloat(),'f',2)
                            +", '"+unit+"', "+ui->lineEdit_9->text()+")"))
                    QMessageBox::critical(NULL,QObject::tr("Ошибка"),query5.lastError().text());
            }
            QSqlQuery query6(mdl->database());
            if(!query6.exec("UPDATE goods SET amount_at_storage = amount_at_storage + "+QString::number(ui->lineEdit_2->text().toDouble(),'f',2)+" WHERE id = "+ui->lineEdit_4->text()))
                QMessageBox::critical(NULL,QObject::tr("Ошибка"),query6.lastError().text());
        }
        if(!mdl->submitAll())
            QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
        mdl->select();
    }
    else
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),"Заполните пустые поля");
}
void deliveries::id_1(int r)
{
    ui->lineEdit_4->setText(QString::number(r));
}
void deliveries::id_2(int r)
{
    ui->lineEdit_6->setText(QString::number(r));
}
void deliveries::id_3(int r)
{
    ui->lineEdit_9->setText(QString::number(r));
}
void deliveries::id_4(int r)
{
    ui->lineEdit_10->setText(QString::number(r));
}
void deliveries::id_5(int r)
{
    ui->lineEdit_5->setText(QString::number(r));
}

void deliveries::on_pushButton_Del_clicked()
{
    if(mdl->rowCount()!=0)
    {
        int selRow = ui->tableView->currentIndex().row();
        if(selRow >= 0)
        {
            mdl->removeRow(selRow);
            if(!mdl->submitAll())
                QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
            mdl->select();
        }
    }
}
void deliveries::on_pushButton_Ret_clicked()
{
    mdl->revertAll();
    if(!mdl->submitAll())
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
    if(!mdl->select())
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
}

void deliveries::on_pushButton_clicked()
{
    goods* form = new goods(nullptr,new QSqlDatabase(mdl->database()),true);
    connect(form,SIGNAL(ret_id(int)),this,SLOT(id_1(int)));
    form->show();
}

void deliveries::on_pushButton_2_clicked()
{
    dealers* form = new dealers(nullptr,new QSqlDatabase(mdl->database()),true);
    connect(form,SIGNAL(ret_id(int)),this,SLOT(id_2(int)));
    form->show();
}

void deliveries::on_pushButton_1_clicked()
{
    storage* form = new storage(nullptr,new QSqlDatabase(mdl->database()),true);
    connect(form,SIGNAL(ret_id(int)),this,SLOT(id_3(int)));
    form->show();
}

void deliveries::on_pushButton_3_clicked()
{
    print* form = new print(nullptr,new QSqlDatabase(mdl->database()),true);
    connect(form,SIGNAL(ret_id(int)),this,SLOT(id_4(int)));
    form->show();
}

void deliveries::on_pushButton_4_clicked()
{
    bill* form = new bill(nullptr,new QSqlDatabase(mdl->database()),true);
    connect(form,SIGNAL(ret_id(int)),this,SLOT(id_5(int)));
    form->show();
}
