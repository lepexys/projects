#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QFile>
#include "QDuty.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE

class Form : public QWidget
{
    Q_OBJECT

public:
    void readFromFile(const QString &fileName);
    Form(QWidget *parent = nullptr);
    Form(const Duty &contacts, QObject *parent = nullptr);
    ~Form();

private:
    Ui::Form *ui;
    QVector<Duty> dutys;
};

#endif // FORM_H
