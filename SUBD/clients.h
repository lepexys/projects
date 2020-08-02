#ifndef CLIENTS_H
#define CLIENTS_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class clients;
}
QT_END_NAMESPACE

class clients : public QWidget
{
    Q_OBJECT
public:
    clients(QWidget *parent = nullptr,QSqlDatabase *db = nullptr, bool d = false);
    QSqlTableModel *mdl;
signals:
    void ret_id(int);
public slots:

private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_Cho_clicked();

private:
    Ui::clients *ui;
};

#endif // CLIENTS_H
