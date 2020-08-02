#ifndef GLPP_H
#define GLPP_H

#include<QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Qt>
#include <QDebug>
#include <QKeyEvent>

class GLPP : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLPP(QWidget* parent = nullptr);
    ~GLPP();
    void createRegularPolygon(int);
    void DrawPoints(int);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    virtual void keyPressEvent(QKeyEvent*);

signals:

public slots:
};

#endif // GLPP_H
