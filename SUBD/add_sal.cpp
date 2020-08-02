#include "add_sal.h"
#include "ui_add_sal.h"
#include <QSqlError>
#include <QMessageBox>

add_sal::add_sal(QWidget *parent,QSqlDatabase *db) : QWidget(parent)
  ,ui(new Ui::add_sal)
{
    ui->setupUi(this);
    mdl = new QSqlTableModel(this,*db);
    mdl->setTable("sales_contract");
    mdl->select();
}

void add_sal::on_pushButton_Ok_clicked()
{
    if(!ui->lineEdit->text().isEmpty())
    {
    QSqlQuery query(mdl->database());
    query.prepare(QString("INSERT INTO sales_contract VALUES (:number, :conclusion_date, :expiration_date, :description)"));
    query.bindValue(":number",QString(ui->lineEdit->text()));
    query.bindValue(":conclusion_date",QString(ui->dateEdit->text()));
    query.bindValue(":expiration_date",QString(ui->dateEdit_2->text()));
    query.bindValue(":description",QString(ui->textEdit->toPlainText()));
    if(!query.exec())
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),query.lastError().text());
    if(!mdl->submitAll())
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
    mdl->select();
    ui->textEdit->setText("");
    }
    else
    {
        QSqlQuery query(mdl->database());
        query.prepare(QString("INSERT INTO sales_contract (conclusion_date, expiration_date, description) VALUES (:conclusion_date, :expiration_date, :description)"));
        query.bindValue(":conclusion_date",QString(ui->dateEdit->text()));
        query.bindValue(":expiration_date",QString(ui->dateEdit_2->text()));
        query.bindValue(":description",QString(ui->textEdit->toPlainText()));
        if(!query.exec())
            QMessageBox::critical(NULL,QObject::tr("Ошибка"),query.lastError().text());
        if(!mdl->submitAll())
            QMessageBox::critical(NULL,QObject::tr("Ошибка"),mdl->lastError().text());
        mdl->select();
        ui->textEdit->setText("");
    }
}

void add_sal::id(QString r)
{
    ui->lineEdit_2->setText(r);
}

void add_sal::on_pushButton_Print_clicked()
{
    print* form = new print(nullptr,new QSqlDatabase(mdl->database()));
    form->show();
}

void add_sal::on_pushButton_Add_clicked()
{
    ui->textEdit->append(QString("Продукт \""+ui->lineEdit_2->text()+"\"  в количестве:"+ui->doubleSpinBox->text()+" ед.  по цене "+ui->doubleSpinBox_2->text()+"р."));
}

void add_sal::on_pushButton_2_clicked()
{
    goods* form = new goods(nullptr,new QSqlDatabase(mdl->database()),true);
    connect(form,SIGNAL(ret_str(QString)),this,SLOT(id(QString)));
    form->show();
}
