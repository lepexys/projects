#ifndef DELIVERIES_H
#define DELIVERIES_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "goods.h"
#include "dealers.h"
#include "bill.h"
#include "storage.h"
#include "print.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class deliveries;
}
QT_END_NAMESPACE

class deliveries : public QWidget
{
    Q_OBJECT
public:
    deliveries(QWidget *parent = nullptr,QSqlDatabase *db = nullptr);
    QSqlTableModel *mdl;

signals:

public slots:

private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_Ret_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_1_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void id_1(int);
    void id_2(int);
    void id_3(int);
    void id_4(int);
    void id_5(int);

private:
    Ui::deliveries *ui;
};

#endif // DELIVERIES_H
