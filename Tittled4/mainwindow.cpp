#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"
#include "dialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
     ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Form *f1 = new Form();
    f1->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog *dio = new Dialog();
    dio->show();
}
