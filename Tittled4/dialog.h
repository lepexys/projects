#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>
#include "QDuty.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Dialog;
}
QT_END_NAMESPACE

class Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    void readFromFile(const QString &fileName);
    void writeToFile(const QString &fileName);
    ~Dialog();

private:
    Ui::Dialog *ui;
    Duty duty;
};

#endif // DIALOG_H
