#ifndef PRINT_H
#define PRINT_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class print;
}
QT_END_NAMESPACE


class print : public QWidget
{
    Q_OBJECT
public:
    print(QWidget *parent = nullptr,QSqlDatabase *db = nullptr, bool d = false);
    QSqlTableModel *mdl;
    bool is_sales = false;

signals:
    void ret_id(int);
public slots:
private slots:
    void on_pushButton_Cho_clicked();

    void on_pushButton_Print_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_pushButton_Del_clicked();

private:
    Ui::print *ui;
};

#endif // PRINT_H
