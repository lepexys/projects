#include "mainwindow.h"
#include "glpp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GLPP glp;
    glp.show();
    glp.setFocusPolicy(Qt::FocusPolicy::StrongFocus);
    return a.exec();
}
