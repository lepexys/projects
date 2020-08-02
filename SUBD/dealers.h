#ifndef DEALERS_H
#define DEALERS_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class dealers;
}
QT_END_NAMESPACE

class dealers : public QWidget
{
    Q_OBJECT
public:
    dealers(QWidget *parent = nullptr,QSqlDatabase *db = nullptr, bool d = false);
    QSqlTableModel *mdl;

signals:
    void ret_id(int);
public slots:

private slots:
    void on_pushButton_Add_clicked();

    void on_pushButton_Del_clicked();

    void on_pushButton_Cho_clicked();

private:
    Ui::dealers *ui;
};

#endif // DEALERS_H
