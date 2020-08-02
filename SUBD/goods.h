#ifndef GOODS_H
#define GOODS_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class goods;
}
QT_END_NAMESPACE

class goods : public QWidget
{
    Q_OBJECT
public:
    goods(QWidget *parent = nullptr,QSqlDatabase *db = nullptr, bool d = false);
    QSqlTableModel *mdl;
    bool dialog;

signals:
    void ret_id(int);
    void ret_str(QString);
private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_Ret_clicked();

    void on_pushButton_Cho_clicked();

private:
    Ui::goods *ui;
};

#endif // GOODS_H
