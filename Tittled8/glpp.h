#ifndef GLPP_H
#define GLPP_H

#include<QOpenGLWidget>
#include <QOpenGLFunctions>
#include <Qt>
#include <QDebug>
#include <QKeyEvent>
#include <QAction>
#include <QtWidgets>

class GLPP : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    GLPP(QWidget* parent = nullptr);
    ~GLPP();
    void createRegularPolygon(int);
    void DrawPoints(int);

protected:
    struct Body;
    struct Dog;
    void Draw(Body*,float,float, float);
    void Draw(Body*,unsigned int);
    void initializeGL();
    void paintGL();
    void resizeGL(int, int);
    void DrawDog(Dog*);
    void DrawMan();
    void UpdateEvent();
    void createRoom(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat,int);
    virtual void keyPressEvent(QKeyEvent*);
    virtual void keyReleaseEvent(QKeyEvent*);
    Dog *k9;

signals:

public slots:
};

#endif // GLPP_H
