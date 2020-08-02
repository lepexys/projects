#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QAction>
#include <QThread>
#include <QTime>
#include <cmath>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

struct MyThread : QThread
{
    Q_OBJECT
public:
    explicit MyThread();
    void run ();
    int gcd(int,int);
signals:
    void add();
};
class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
