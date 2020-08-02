#include "Frame.h"

MyFrame::MyFrame()
{
   this->installEventFilter(this);
}

bool MyFrame::eventFilter(QObject *object, QEvent *event)
{
    if (object == this && event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Forward||Qt::Key_Down||Qt::Key_Right||Qt::Key_Left) {
                return true;
            } else {
                return false;
            }
        }
    return false;
}
