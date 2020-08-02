#include "mainwindow.h"
#include <QtWidgets>
#include "ui_mainwindow.h"
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    QString tm = QTime :: currentTime().toString("hh:mm:ss");
     ui->textBrowser->setText(tm);
    timer->start(1000);
    connect(timer, &QTimer::timeout, [&] ()
    {
                tm = QTime :: currentTime().toString("hh:mm:ss");
                ui->textBrowser->setText(tm);
    });
    setWindowTitle("Digital Clock");
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_triggered()
{
QMessageBox* a = new QMessageBox();
a->setText("This is clock");
a->exec();
}

void MainWindow::on_action_2_triggered()
{
    close();
}
