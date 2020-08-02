#include "storage.h"
#include "ui_storage.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlRecord>


storage::storage(QWidget *parent,QSqlDatabase *db, bool d) : QWidget(parent)
  ,ui(new Ui::storage)
{
    ui->setupUi(this);
    mdl = new QSqlTableModel(this,*db);
    mdl->setTable("storage");
    mdl->select();
    mdl->setHeaderData(0,Qt::Horizontal,"№ Продукта");
    mdl->setHeaderData(1,Qt::Horizontal,"№ Поля");
    mdl->setHeaderData(2,Qt::Horizontal,"Количество");
    mdl->setHeaderData(3,Qt::Horizontal,"Единицы");
    mdl->setHeaderData(4,Qt::Horizontal,"Код склада");
    ui->tableView->setModel(mdl);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() + ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2) + ui->tableView->columnWidth(3) + ui->tableView->columnWidth(4));
    ui->tableView->setGeometry(rect);
    if(d)
    {
        ui->pushButton_Del->setEnabled(false);
    }
    else
    {
        ui->pushButton_Cho->setEnabled(false);
    }
}


void storage::on_pushButton_Del_clicked()
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


void storage::on_pushButton_Cho_clicked()
{
    if(mdl->rowCount()!=0)
    {
        int selRow = ui->tableView->currentIndex().row();
        if(selRow >= 0)
        {
            emit ret_id(mdl->record(selRow).value(4).toInt());
            close();
        }
    }
}
