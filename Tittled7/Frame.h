#ifndef FRAME_H
#define FRAME_H
#include <QFrame>
#include <QKeyEvent>
#include <Qt>

class MyFrame : public QFrame
{
    Q_OBJECT

public:
    MyFrame();
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // FRAME_H
