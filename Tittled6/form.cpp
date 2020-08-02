#include "form.h"
#include "mainwindow.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    int n = ui->textEdit->toPlainText().toInt();
    MainWindow* lulw = new MainWindow(this,n);
    lulw->show();
    lulw->Elevator();
}
