#ifndef BILL_H
#define BILL_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QSqlRecord>

QT_BEGIN_NAMESPACE
namespace Ui {
class bill;
}
QT_END_NAMESPACE

class SqlTableModel : public QSqlTableModel {
public:
    explicit SqlTableModel(QObject *parent = 0);
    QVariant data(const QModelIndex &index, int role) const override;
    int columnCount(const QModelIndex &parent) const override;
};

class bill : public QWidget
{
    Q_OBJECT
public:
    bill(QWidget *parent = nullptr,QSqlDatabase *db = nullptr, bool d = false);
    SqlTableModel *mdl;

signals:
    void ret_id(int);
public slots:

private slots:

    void on_pushButton_Del_clicked();

    void on_pushButton_Cho_clicked();

private:
    Ui::bill *ui;
};

#endif // BILL_H
