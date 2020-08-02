#include "mainwindow.h"
#include "ui_mainwindow.h"


MyThread::MyThread()
{
}
int MyThread::gcd (int a,int b)
{
    while (a!=0 && b!=0)
    {
        if (a>b) {
            a=a%b;
        }
        else b=b%a;
    }
    return a+b;
}
void MyThread::run()
{
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());
    for(int i = 0; i <= 100; i++)
    {
        int random[1000];
        for(int k = 0;k<1000;k++)
        {
            int sum = 0;
            random[k] = qrand()%200000 + 800000;
            for (int j = 1;j<floor(sqrt(random[k]));j++)
            {
                if(random[k] % j == 0)
                    sum += j;
            }
            random[k] = sum;
        }
        for(int l = 0;l<999;l++)
        {
            int max = 0;
            for(int u = l;u<999;u++)
            {
                max = (gcd(random[l],random[u]) > max)?gcd(random[l],random[u]):max;
            }
            random[l]=max;
        }
        emit add();
    }
};
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(10);
    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setColumnWidth(1,300);
    ui->tableWidget->setHorizontalHeaderLabels({"Готовность","Процесс выполнения"});
    MyThread** tmas = new MyThread*[10];
    QLabel** check = new QLabel*[10];
    QProgressBar** prog = new QProgressBar*[10];
    for(int i = 0;i<10;i++)
    {
        tmas[i] = new MyThread();
        check[i] = new QLabel("X",this);
        prog[i] = new QProgressBar(this);
        connect(prog[i], &QProgressBar::valueChanged, this, [=](){ if(prog[i]->value() == 100) check[i]->setText("✔"); });
        ui->tableWidget->setCellWidget(i,0,check[i]);
        ui->tableWidget->setCellWidget(i,1,prog[i]);
        connect(tmas[i],&MyThread::add,this, [=] () { prog[i]->setValue(prog[i]->value()+1);  });
        tmas[i]->start();
    }
}



MainWindow::~MainWindow()
{
    delete ui;
}

