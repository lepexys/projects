#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QLogValueAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>
#include "Lister.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr,int n = 5);
    void Elevator();
    void PaintEvent();
    ~MainWindow();
    Lister* l1,*l2;
    bool k;
    int max;
    double le1,le2;
    bool dwn1,dwn2;
    int shw;
    QChartView *chartView;
    QLineSeries *series1,*series2;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
