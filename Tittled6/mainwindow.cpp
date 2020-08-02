#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAction>
#include <QTimer>


using namespace QtCharts;

MainWindow::MainWindow(QWidget *parent,int n)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    l1 = nullptr;
    l2 = nullptr;
    max = n;
    k = true;
    le1 = max-1;
    le2 = 0.0;
    dwn1 = true;
    dwn2 = false;
    shw = 0;
}

int del1 = 0,del2 = 0;
long tmer = 0,d1 = 0,d2 = 0;
QVector<double> xvec1(0),yvec1(0),xvec2(0),yvec2(0);
QTimer *timer;

bool is_equal(double x, double y) {
    return std::fabs(x - y) < std::numeric_limits<double>::epsilon()*100000000;
}
void MainWindow::PaintEvent()
{
    if(k)
    {
        if(shw)
           shw-=1;
        else
        {
            ui->add1->setText("");
            ui->add2->setText("");
            ui->hey->setText("");
        }
        if(!del1)
        {
            if(l1 != nullptr)
            {
            if(is_equal(trunc(le1+0.1), le1))
            {
                Lister* cur1 = l1;
                bool is_another1 = false,isit = true;
                while(cur1 != nullptr)
                {
                    if(dwn1)
                    {
                        if(cur1->num < static_cast< int >(trunc(le1+0.1)))
                            is_another1 = true;
                    }
                    else
                    {
                        if(cur1->num > static_cast< int >(trunc(le1+0.1)))
                            is_another1 = true;
                    }
                    if(cur1->num == static_cast< int >(trunc(le1+0.1)))
                    {
                        del1 = 5;
                        Lister* temp1 = cur1;
                        temp1 = temp1->Delete();
                        if(temp1 == nullptr)
                            l1 = nullptr;
                        else
                        {
                        while(temp1->prev != nullptr)
                        {
                            temp1 = temp1->prev;
                        }
                        l1 = temp1;
                        }
                        isit = false;
                    }
                    cur1 = cur1->next;
                }
                if(!is_another1)
                    dwn1 = !dwn1;
                if(isit)
                {
                    if(dwn1)
                        le1-=(double)1/5;
                    else
                        le1+=(double)1/5;
                }
            }
            else
                if(dwn1)
                    le1-=(double)1/5;
                else
                    le1+=(double)1/5;
            *series1 << QPointF((qreal)tmer/5,(qreal)d1);
            }
            else
            {
                d1+=1;
                *series1 << QPointF((qreal)tmer/5,(qreal)d1);
            }
        }
            else
        {
            d1+=1;
            *series1 << QPointF((qreal)tmer/5,(qreal)d1);
            del1-=1;
        }
        if(!del2)
        {
            if(l2 != nullptr)
            {
            if(is_equal(trunc(le2+0.1), le2))
            {
                Lister* cur2 = l2;
                bool is_another = false,isit = true;
                while(cur2 != nullptr)
                {
                    if(dwn2)
                    {
                        if(cur2->num < static_cast< int >(trunc(le2+0.1)))
                            is_another = true;
                    }
                    else
                    {
                        if(cur2->num > static_cast< int >(trunc(le2+0.1)))
                            is_another = true;
                    }
                    if(cur2->num == static_cast< int >(trunc(le2+0.1)))
                    {
                        del2 = 5;
                        Lister* temp2 = cur2;
                        temp2 = temp2->Delete();
                        if(temp2 == nullptr)
                            l2 = nullptr;
                        else
                        {
                        while(temp2->prev != nullptr)
                        {
                            temp2 = temp2->prev;
                        }
                        l2 = temp2;
                        }
                        isit = false;
                    }
                    cur2 = cur2->next;
                }
                if(!is_another)
                    dwn2 = !dwn2;
                if(isit)
                {
                    if(dwn2)
                        le2-=(double)1/5;
                    else
                        le2+=(double)1/5;
                }
            }
            else
                if(dwn2)
                    le2-=(double)1/5;
                else
                    le2+=(double)1/5;
            *series2 << QPointF((qreal)tmer/5,(qreal)d2);
            }
            else
            {
                d2+=1;
                *series2 << QPointF((qreal)tmer/5,(qreal)d2);
            }
        }
            else
        {
            d2+=1;
            *series2 << QPointF((qreal)tmer/5,(qreal)d2);
            del2-=1;
        }
        ui->level1->setText(QString::number(le1,'g',3));
        ui->level2->setText(QString::number(le2,'g',3));
        xvec1.append(tmer);
        yvec1.append(le1);
        xvec2.append(tmer);
        yvec2.append(le2);
        tmer+=1;
    }
}

void MainWindow::Elevator()
{
    timer = new QTimer(this);
    timer->start(200);
    chartView = new QChartView(this);
    series1 = new QLineSeries();
    series2 = new QLineSeries();
    connect(timer, &QTimer::timeout, [&] ()
    {
        PaintEvent();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if(k)
    {
        int e = rand()%max;
        bool one = true;
        double dis1,dis2;
        if(dwn1)
            dis1= le1-e;
        else
            dis1= e-le1;
        if(dwn2)
            dis2= le2-e;
        else
            dis2= e-le2;
        if(l1 == nullptr && l2 == nullptr)
        {
            if(sqrt(dis1*dis1)>sqrt(dis2*dis2))
            {
                Lister* sos = new Lister(e,l2,nullptr);
                l2 = sos;
                one = false;
                if(dis2<0)
                dwn2 = !dwn2;
            }
            else
            {
                Lister* sos = new Lister(e,l1,nullptr);
                l1 = sos;
                one = true;
                if(dis1<0)
                dwn1 = !dwn1;
            }
        }
        else
        {
            if(l1 == nullptr)
            {
                if(dis2<0)
                {
                    if(dis1<0)
                        dwn1 = !dwn1;
                    Lister* sos = new Lister(e,l1,nullptr);
                    if(l1!=nullptr)
                    l1->prev = sos;
                    l1 = sos;
                    one = true;
                }
                else
                {
                    if(sqrt(dis1*dis1)>dis2)
                    {
                        Lister* sos = new Lister(e,l2,nullptr);
                        if(l2!=nullptr)
                        l2->prev = sos;
                        l2 = sos;
                        one = false;
                    }
                    else
                    {
                        if(dis1<0)
                            dwn1 = !dwn1;
                        Lister* sos = new Lister(e,l1,nullptr);
                        if(l1!=nullptr)
                        l1->prev = sos;
                        l1 = sos;
                        one = true;
                    }
                }
            }
            else
            {
            if(l2 == nullptr)
            {
                if(dis1<0)
                {
                    if(dis2<0)
                        dwn2 = !dwn2;
                    Lister* sos = new Lister(e,l2,nullptr);
                    if(l2!=nullptr)
                    l2->prev = sos;
                    l2 = sos;
                    one = false;
                }
                else
                {
                    if(sqrt(dis2*dis2)>dis1)
                    {
                        Lister* sos = new Lister(e,l1,nullptr);
                        if(l1!=nullptr)
                        l1->prev = sos;
                        l1 = sos;
                        one = true;
                    }
                    else
                    {
                        if(dis2<0)
                            dwn2 = !dwn2;
                        Lister* sos = new Lister(e,l2,nullptr);
                        if(l2!=nullptr)
                        l2->prev = sos;
                        l2 = sos;
                        one = false;
                    }
                }
            }
                else
                {
                    if(dis1<0)
                    {
                        if(dis2<0)
                        {
                            if(dis1>dis2)
                            {
                                Lister* sos = new Lister(e,l1,nullptr);
                                if(l1!=nullptr)
                                l1->prev = sos;
                                l1 = sos;
                                one = true;
                                dwn1 = !dwn1;
                            }
                            else
                            {
                                Lister* sos = new Lister(e,l2,nullptr);
                                if(l2!=nullptr)
                                l2->prev = sos;
                                l2 = sos;
                                one = false;
                                dwn2 = !dwn2;
                            }
                        }
                        else
                        {
                            Lister* sos = new Lister(e,l2,nullptr);
                            if(l2!=nullptr)
                            l2->prev = sos;
                            l2 = sos;
                            one = false;
                        }
                    }
                    else
                    {
                        if(dis2<0)
                        {
                            Lister* sos = new Lister(e,l1,nullptr);
                            if(l1!=nullptr)
                            l1->prev = sos;
                            l1 = sos;
                            one = true;
                        }
                        else
                        {
                            if(dis1>dis2)
                            {
                                Lister* sos = new Lister(e,l2,nullptr);
                                if(l2!=nullptr)
                                l2->prev = sos;
                                l2 = sos;
                                one = false;
                            }
                            else
                            {
                                Lister* sos = new Lister(e,l1,nullptr);
                                if(l1!=nullptr)
                                l1->prev = sos;
                                l1 = sos;
                                one = true;
                            }
                        }
                    }
                }
            }
        }
        ui->hey->setText(QString::number(e));
        if(one)
            ui->add1->setText("ME");
        else
            ui->add2->setText("ME");
        shw = 4;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    if(k)
    {
        k=!k;
        ui->pushButton_2->setText("продолжить");
    }
    else
    {
        k=!k;
        ui->pushButton_2->setText("пауза");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->widget->clearGraphs();
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(xvec1,yvec1);
    ui->widget->addGraph();
    ui->widget->graph(1)->setData(xvec2,yvec2);
    ui->widget->xAxis->setLabel("T,s");
    ui->widget->yAxis->setLabel("H,lvl");
    ui->widget->xAxis->setRange(0, tmer);
    ui->widget->yAxis->setRange(0, max);
    ui->widget->replot();
    QChart *chart = new QChart();
    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->legend()->hide();
    chart->setTitle("Graphic");
    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("T, s");
    axisX->setLabelFormat("%i");
    axisX->setTickCount(tmer);
    chart->addAxis(axisX, Qt::AlignBottom);
    series1->attachAxis(axisX);
    series2->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Tw, s");
    axisY->setLabelFormat("%g");
    axisY->setTickCount(tmer);
    chart->addAxis(axisY, Qt::AlignLeft);
    series1->attachAxis(axisY);
    series2->attachAxis(axisY);
    chartView->setChart(chart);
    ui->grid->addWidget(chartView);
}
