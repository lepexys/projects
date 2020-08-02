#ifndef ADD_SAL_H
#define ADD_SAL_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "goods.h"
#include "print.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class add_sal;
}
QT_END_NAMESPACE

class add_sal : public QWidget
{
    Q_OBJECT
public:
    add_sal(QWidget *parent = nullptr,QSqlDatabase *db = nullptr);
    QSqlTableModel *mdl;

signals:

public slots:
void id(QString);
private slots:

    void on_pushButton_Ok_clicked();

    void on_pushButton_Print_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::add_sal *ui;
};

#endif // ADD_SAL_H
