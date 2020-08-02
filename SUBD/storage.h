#ifndef STORAGE_H
#define STORAGE_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui {
class storage;
}
QT_END_NAMESPACE

class storage : public QWidget
{
    Q_OBJECT
public:
    storage(QWidget *parent = nullptr,QSqlDatabase *db = nullptr, bool d = false);
    QSqlTableModel *mdl;

signals:
    void ret_id(int);
public slots:

private slots:

    void on_pushButton_Del_clicked();

    void on_pushButton_Cho_clicked();

private:
    Ui::storage *ui;
};

#endif // STORAGE_H
