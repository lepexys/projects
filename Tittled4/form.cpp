#include "form.h"
#include "ui_form.h"
#include <QTableWidget>
#include <QSettings>

Form::Form(QWidget *parent) : QWidget(parent),
    ui(new Ui::Form),
    dutys()
{
    ui->setupUi(this);
    readFromFile("C:/Qt/QtWork/Tittled4/sht.ini");
}

void Form::readFromFile(const QString &fileName)
{
    QSettings sett(fileName, QSettings::IniFormat);
    QStringList lst;
    lst<< "Фамилия" << "Дата" << "Долг";
    ui->tableWidget = new QTableWidget(10, 3, this);
    ui->tableWidget->setHorizontalHeaderLabels(lst);
    ui->tableWidget->setGeometry(200,60,330,360);
    for(int row=0; row!=ui->tableWidget->rowCount(); ++row){
        QString s = QString::number(row);
        sett.beginGroup(s);
        QTableWidgetItem *newItem = new QTableWidgetItem(sett.value("name", "").toString());
        ui->tableWidget->setItem(row, 0, newItem);
        newItem = new QTableWidgetItem(sett.value("date", "").toString());
        ui->tableWidget->setItem(row, 1, newItem);
        newItem = new QTableWidgetItem(sett.value("dolg", "").toString());
        ui->tableWidget->setItem(row, 2, newItem);
        sett.endGroup();
    }
}

Form::~Form()
{
    delete ui;
}
