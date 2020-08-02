#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlError>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5433);
    db.setDatabaseName("Dab");
    db.setUserName("postgres");
    db.setPassword("vila23");
    if(!db.open())
    {
        QMessageBox::critical(NULL,QObject::tr("Ошибка"),db.lastError().text());
        exit(0);
    }
    else
    {

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    add_del* w = new add_del(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_4_clicked()
{
    deliveries* w = new deliveries(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_7_clicked()
{
    dealers* w = new dealers(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    goods* w = new goods(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_8_clicked()
{
    bill* w = new bill(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_9_clicked()
{
    storage* w = new storage(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    add_sal* w = new add_sal(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_5_clicked()
{
    sales* w = new sales(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_6_clicked()
{
    clients* w = new clients(nullptr,&db);
    w->show();
}

void MainWindow::on_pushButton_10_clicked()
{
    print* w = new print(nullptr,&db);
    w->show();
}
