#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMessageBox>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
private slots:
    void spr(){
        QMessageBox msg;
        msg.setText("It is a clock!");
        msg.exec();
    }
    void exit(){
        close();
    }
    void on_action_triggered();
    void on_action_2_triggered();
};
#endif // MAINWINDOW_H
