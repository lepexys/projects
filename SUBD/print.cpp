#include "print.h"
#include "ui_print.h"
#include <QSqlRecord>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextDocumentWriter>
#include <QSqlError>
#include <QMessageBox>


print::print(QWidget *parent,QSqlDatabase *db, bool d) : QWidget(parent)
  ,ui(new Ui::print)
{
    ui->setupUi(this);
    mdl = new QSqlTableModel(this,*db);
    mdl->setTable("sales_contract");
    mdl->select();
    mdl->setHeaderData(0,Qt::Horizontal,"№ Договора");
    mdl->setHeaderData(1,Qt::Horizontal,"Дата заключения");
    mdl->setHeaderData(2,Qt::Horizontal,"Дата истечения");
    mdl->setHeaderData(3,Qt::Horizontal,"Описание");
    ui->tableView->setModel(mdl);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() + ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2) + ui->tableView->columnWidth(3));
    ui->tableView->setGeometry(rect);
    ui->radioButton->setChecked(true);
    if(d)
    {
        ui->pushButton_Print->setEnabled(false);
        ui->pushButton_Del->setEnabled(false);
    }
    else
    {
        ui->pushButton_Cho->setEnabled(false);
    }
}

void print::on_pushButton_Cho_clicked()
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

void print::on_pushButton_Print_clicked()
{
    if(mdl->rowCount()!=0)
    {
        int selRow = ui->tableView->currentIndex().row();
        if(selRow >= 0)
        {
            mdl->record(selRow).value(0).toString();
            QTextDocument doc;
            QTextCursor cur(&doc);
            if(is_sales)
            {
                cur.insertText("    ДОГОВОР НА ПРОДАЖУ №"+mdl->record(selRow).value(0).toString()+"\n\n");
                cur.insertText("Дата заключения: "+mdl->record(selRow).value(1).toString()+"\n");
                cur.insertText("Дата истечения: "+mdl->record(selRow).value(2).toString()+"\n\n");
                cur.insertText("    ПРЕДМЕТ ДОГОВОРА\n\n"+mdl->record(selRow).value(3).toString());
            }
            else
            {
                cur.insertText("    ДОГОВОР НА ПОСТАВКУ №"+mdl->record(selRow).value(0).toString()+"\n\n");
                cur.insertText("Дата заключения: "+mdl->record(selRow).value(1).toString()+"\n");
                cur.insertText("Дата истечения: "+mdl->record(selRow).value(2).toString()+"\n\n");
                cur.insertText("    ПРЕДМЕТ ДОГОВОРА\n\n"+mdl->record(selRow).value(3).toString());
            }
            QTextDocumentWriter writer("test.odt");
            writer.setFormat("odf");
            writer.write(&doc);
        }
    }
}

void print::on_radioButton_clicked()
{
    is_sales = true;
    mdl->setTable("sales_contract");
    mdl->select();
    mdl->setHeaderData(0,Qt::Horizontal,"№ Договора");
    mdl->setHeaderData(1,Qt::Horizontal,"Дата заключения");
    mdl->setHeaderData(2,Qt::Horizontal,"Дата истечения");
    mdl->setHeaderData(3,Qt::Horizontal,"Описание");
    ui->tableView->setModel(mdl);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() + ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2) + ui->tableView->columnWidth(3));
    ui->tableView->setGeometry(rect);
}

void print::on_radioButton_2_clicked()
{
    is_sales = false;
    mdl->setTable("purchase_contract");
    mdl->select();
    mdl->setHeaderData(0,Qt::Horizontal,"№ Договора");
    mdl->setHeaderData(1,Qt::Horizontal,"Дата заключения");
    mdl->setHeaderData(2,Qt::Horizontal,"Дата истечения");
    mdl->setHeaderData(3,Qt::Horizontal,"Описание");
    ui->tableView->setModel(mdl);
    QRect rect = ui->tableView->geometry();
    rect.setWidth(2 + ui->tableView->verticalHeader()->width() + ui->tableView->columnWidth(0) + ui->tableView->columnWidth(1) + ui->tableView->columnWidth(2) + ui->tableView->columnWidth(3));
    ui->tableView->setGeometry(rect);
}

void print::on_pushButton_Del_clicked()
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
