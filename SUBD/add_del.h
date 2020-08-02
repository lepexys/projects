#ifndef ADD_DEL_H
#define ADD_DEL_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include "goods.h"
#include "print.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class add_del;
}
QT_END_NAMESPACE

class add_del : public QWidget
{
    Q_OBJECT
public:
    add_del(QWidget *parent = nullptr,QSqlDatabase *db = nullptr);
    QSqlTableModel *mdl;

signals:

public slots:
void id(QString);
private slots:

    void on_pushButton_Ok_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_Add_clicked();

    void on_pushButton_Print_clicked();

private:
    Ui::add_del *ui;
};

#endif // ADD_DEL_H
