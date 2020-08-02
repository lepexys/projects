#include "goods.h"
#include "ui_goods.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>


goods::goods(QWidget *parent,QSqlDatabase *db, bool d) : QWidget(parent)
  ,ui(new Ui::goods)
{
    dialog = d;
    ui->setupUi(this);
    mdl = new QSqlTableModel(this,*db);
    mdl->setTable("goods");
    mdl->select();
    mdl->setHeaderData(0,Qt::Horizontal,"№");
    mdl->setHeaderData(1,Qt::Horizontal,"Производитель");
    mdl->setHeaderData(2,Qt::Horizontal,"Цена за единицу");
    mdl->setHeaderData(3,Qt::Horizontal,"Артикул");
    mdl->setHeaderData(4,Qt::Horizontal,"Количество на складе");
    mdl->setHeaderData(5,Qt::Horizontal,"Единицы");
    mdl->setHeaderData(6,Qt::Horizontal,"Длина");
    mdl->setHeaderData(7,Qt::Horizontal,"Высота");
    mdl->setHeaderData(8,Qt::Horizontal,"Ширина");
    mdl->setHeaderData(9,Qt::Horizontal,"Масса нетто");
    mdl->setHeaderData(10,Qt::Horizontal,"Масса брутто");
    mdl->setHeaderData(11,Qt::Horizontal,"Ставка НДС");
    mdl->setHeaderData(12,Qt::Horizontal,"Наименование");
    ui->tableView->setModel(mdl);
     ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() + ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2) + ui->tableView->columnWidth(3)
                  + ui->tableView->columnWidth(4) + ui->tableView->columnWidth(5) + ui->tableView->columnWidth(6) + ui->tableView->columnWidth(7) + ui->tableView->columnWidth(8)
                  + ui->tableView->columnWidth(9) + ui->tableView->columnWidth(10) + ui->tableView->columnWidth(11) + + ui->tableView->columnWidth(12));
    ui->tableView->setGeometry(rect);
    if(d)
    {
        ui->pushButton_Add->setEnabled(false);
        ui->pushButton_Del->setEnabled(false);
        ui->pushButton_Ret->setEnabled(false);
    }
    else
    {
        ui->pushButton_Cho->setEnabled(false);
    }
}

void goods::on_pushButton_Add_clicked()
{
    if(!ui->lineEdit_5->text().isEmpty() && !ui->lineEdit_6->text().isEmpty() && !(ui->doubleSpinBox->value() == 0.00) && !ui->lineEdit_8->text().isEmpty()
            && !(ui->doubleSpinBox_5->value() == 0.00))
    {
        QSqlQuery query(mdl->database());
        query.prepare(QString("INSERT INTO goods (producer, price_per_unit, vendor_code, amount_at_storage, units, length, height, width, net_weight, gross_mass, vat_rate, name) "
                              "VALUES (:producer, :price_per_unit, :vendor_code, :amount_at_storage, :units, :length, :height, :width, :net_weight, :gross_mass, :vat_rate, :name)"));
        query.bindValue(":producer",ui->lineEdit_6->text());
        query.bindValue(":price_per_unit",QString::number(ui->doubleSpinBox->value(),'f',2));
        query.bindValue(":vendor_code",ui->lineEdit_8->text());
        query.bindValue(":amount_at_storage",QString::number(0,'f',2));
        query.bindValue(":units",ui->lineEdit_9->text().isEmpty()?"шт.":ui->lineEdit_9->text());
        query.bindValue(":length",QString::number(ui->doubleSpinBox_2->value(),'f',2));
        query.bindValue(":height",QString::number(ui->doubleSpinBox_3->value(),'f',2));
        query.bindValue(":width",QString::number(ui->doubleSpinBox_4->value(),'f',2));
        query.bindValue(":net_weight",QString::number(ui->doubleSpinBox_5->value(),'f',2));
        query.bindValue(":gross_mass",QString::number(ui->doubleSpinBox_6->value(),'f',2));
        query.bindValue(":vat_rate",QString::number(ui->doubleSpinBox_7->value(),'f',2));
        query.bindValue(":name",ui->lineEdit_5->text());
        if(!query.exec())
            QMessageBox::critical(NULL,QObject::tr("Ошибка"),query.lastError().text());
        if(!mdl->submitAll())
            QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
        mdl->select();
    }
    else
    {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),"Заполните поля: Производитель, Цена за единицу, Артикул, Название, Единицы измерения, Масса нетто");
    }
}

void goods::on_pushButton_Del_clicked()
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


void goods::on_pushButton_Ret_clicked()
{
    mdl->revertAll();
    if(!mdl->select())
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
}

void goods::on_pushButton_Cho_clicked()
{
    if(mdl->rowCount()!=0)
    {
        int selRow = ui->tableView->currentIndex().row();
        if(selRow >= 0)
        {
            emit ret_id(mdl->record(selRow).value(0).toInt());
            emit ret_str(mdl->record(selRow).value(12).toString());
            close();
        }
    }
}
