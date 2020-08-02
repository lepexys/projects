#include "dealers.h"
#include "ui_dealers.h"
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>
#include <QSqlRecord>

dealers::dealers(QWidget *parent,QSqlDatabase *db, bool d) : QWidget(parent)
  ,ui(new Ui::dealers)
{
    ui->setupUi(this);
    mdl = new QSqlTableModel(this,*db);
    mdl->setTable("dealers");
    mdl->select();
    mdl->setHeaderData(0,Qt::Horizontal,"№");
    mdl->setHeaderData(1,Qt::Horizontal,"Фирма");
    mdl->setHeaderData(2,Qt::Horizontal,"Директор");
    mdl->setHeaderData(3,Qt::Horizontal,"Главный бухгалтер");
    mdl->setHeaderData(4,Qt::Horizontal,"Адрес");
    mdl->setHeaderData(5,Qt::Horizontal,"Телефон");
    mdl->setHeaderData(6,Qt::Horizontal,"Реквизиты");
    mdl->setHeaderData(7,Qt::Horizontal,"ИНН");
    ui->tableView->setModel(mdl);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() + ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2) + ui->tableView->columnWidth(3)
                  + ui->tableView->columnWidth(4) + ui->tableView->columnWidth(5) + ui->tableView->columnWidth(6) + ui->tableView->columnWidth(7) + ui->tableView->columnWidth(8));
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

void dealers::on_pushButton_Add_clicked()
{
    QString q = QString("INSERT INTO dealers (firm_name, dirrector, accountant_general, adress, telephone, requisites, tin) "
            "VALUES ('"+QString(ui->lineEdit_4->text())+"', '"+QString(ui->lineEdit_6->text())+"', '"+QString(ui->lineEdit_7->text())
            +"', '"+QString(ui->lineEdit_2->text())+"', '"+QString(ui->lineEdit_8->text())+"', '"+QString(ui->lineEdit_9->text())+"', '"+QString(ui->lineEdit_10->text())+"')");
    qDebug()<<q;
    QSqlQuery query(mdl->database());
    if(!query.exec(q))
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),query.lastError().text());
    if(!mdl->submitAll())
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
    mdl->select();
}

void dealers::on_pushButton_Del_clicked()
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

void dealers::on_pushButton_Cho_clicked()
{
    if(mdl->rowCount()!=0)
    {
        int selRow = ui->tableView->currentIndex().row();
        if(selRow >= 0)
        {
            emit ret_id(mdl->record(selRow).value(0).toInt());
            close();
        }
    }
}
