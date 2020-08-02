#include "glpp.h"
#include <qmath.h>
#include <QVector2D>
#include <glm/glm.hpp>
using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>

using namespace std;
GLPP::GLPP(QWidget *parent) : QOpenGLWidget(parent)
{
}

GLPP::~GLPP()
{

}

const char *vertexShader = "attribute vec2 coord2d;\n"
                           "attribute vec3 color;\n"
                           "varying vec3 vColor;\n"                           
                           "uniform mat4 RotationMatrix;\n"
                           "    void main(void) {\n"
                           "    gl_Position = RotationMatrix * vec4(coord2d.x, coord2d.y, 0.0f, 1.0f);\n"
                           "    vColor = color;\n"
                           " }\n";

const char *fragmentShader =
                           "varying vec3 vColor;\n"
                           "    void main(void) {\n"
                           "    gl_FragColor[0] = vColor.r;\n"
                           "    gl_FragColor[1] = vColor.g;\n"
                           "    gl_FragColor[2] = vColor.b;\n"
                           " }\n";
GLint attributeCoord2d;
GLint attributeColor;
GLuint program;
GLfloat degree=0.0f;
GLfloat xd=0.0f;
GLfloat yd=0.0f;

void GLPP::DrawPoints(int n)
{
    GLfloat *polygon_vertex,*polygon_colors;
    polygon_vertex = new GLfloat[n*2];
    polygon_colors = new GLfloat[n*3];
    for (int x = 0, y = 1; y < n * 2; x += 2, y += 2)
    {
        polygon_vertex[x]=rand()%200/(float)100-1.0f;
        polygon_vertex[y]=rand()%200/(float)100-1.0f;
    }
    for (int r = 0, g = 1, b = 2, point = 0; b < n*3; r += 3, g += 3, b+=3, point += 1)
    {
       polygon_colors[r] = rand()%255/255;
       polygon_colors[g] = rand()%255/255;
       polygon_colors[b] = rand()%255/255;
    }
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    GLuint *vboIds = new GLuint[2];
    glGenBuffers(2,vboIds);
    attributeCoord2d = glGetAttribLocation( program, "coord2d");
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * 2 * n, polygon_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeCoord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(attributeCoord2d);


    attributeColor = glGetAttribLocation( program, "color");
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_colors) * n * 3, polygon_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(attributeColor);


    glDrawArrays(GL_POINTS,0,n);

    glDisableVertexAttribArray(attributeCoord2d);
    glDisableVertexAttribArray(attributeColor);

     delete[] polygon_vertex;
     delete[] polygon_colors;
    update();
}

void GLPP::createRegularPolygon(int sides)
{
    GLfloat *polygon_vertex;
    GLfloat *polygon_colors;

    int num_vertices = sides + 2;
    int vertices_array_size = 2 * num_vertices;
    polygon_vertex = new GLfloat[vertices_array_size];
    polygon_colors = new GLfloat[num_vertices*3];

    const float xAngle = M_PI / static_cast<float>(sides);
    const float radius = 0.3f;

    polygon_vertex[0] = 0.0f;
    polygon_vertex[1] = 0.0f;

    for (int x = 2, y = 3, point = 0; point <= sides; x += 2, y += 2, point += 1)
    {
       float angle = 2.0f * static_cast<float>(point) * xAngle;
       polygon_vertex[x] = static_cast<float>(radius * cos(angle));
       polygon_vertex[y] = static_cast<float>(radius * sin(angle));
    }

    for (int r = 0, g = 1, b = 2, point = 0; point < num_vertices; r += 3, g += 3, b+=3, point += 1)
    {
       polygon_colors[r] = 0.078;
       polygon_colors[g] = 0.6f;
       polygon_colors[b] = 0.6f;
    }

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);

        GLuint *vboIds = new GLuint[2];
        glGenBuffers(2,
                     vboIds);


        attributeCoord2d = glGetAttribLocation( program, "coord2d");
        glBindBuffer( GL_ARRAY_BUFFER, vboIds[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * vertices_array_size, polygon_vertex, GL_STATIC_DRAW);
        glVertexAttribPointer(attributeCoord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(attributeCoord2d);


        attributeColor = glGetAttribLocation( program, "color");
        glBindBuffer( GL_ARRAY_BUFFER, vboIds[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_colors) * num_vertices * 3, polygon_colors, GL_STATIC_DRAW);
        glVertexAttribPointer(attributeColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(attributeColor);


        glDrawArrays(
                     GL_TRIANGLE_FAN,
                     0,
                     num_vertices);

        glDisableVertexAttribArray(attributeCoord2d);
        glDisableVertexAttribArray(attributeColor);

         delete[] polygon_vertex;
         delete[] polygon_colors;

}
void GLPP::initializeGL()
{
    initializeOpenGLFunctions();
    GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderId,
                   1,
                   &vertexShader,
                   NULL);
    glCompileShader(vertexShaderId);

    GLint compileOk = GL_FALSE;

    glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &compileOk);
    if (compileOk == GL_FALSE) {
        qDebug() << "shader compile error";
    }
    else {
        qDebug() << "shader compile ok";
    }

    GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId,
                   1,
                   &fragmentShader,
                   NULL);
    glCompileShader(fragmentShaderId);

    glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &compileOk);
    if (compileOk == GL_FALSE) {
        qDebug() << "shader compile error";
    }
    else {
        qDebug() << "shader compile ok";
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShaderId);
    glAttachShader(program, fragmentShaderId);
    glLinkProgram(program);

    GLint linkOk = GL_FALSE;

    glGetProgramiv(program, GL_LINK_STATUS, &linkOk);
    if (linkOk == GL_FALSE) {
        qDebug() << "link error";
    }
    else {
        qDebug() << "link ok";
    }

    glClearColor(0.86f, 0.67f, 0.68f, 1.0);


}

void GLPP::keyPressEvent(QKeyEvent *event)
{
    float lspd = 0.05f;
     switch (event->key())
     {
     case Qt::Key_Escape:
     {
         close();
         break;
     }
     case Qt::Key_Up:
     {
         yd+=lspd*sin(glm::radians(degree));
         xd+=lspd*cos(glm::radians(degree));
         break;
     }
     case Qt::Key_Down:
     {
         yd-=lspd*sin(glm::radians(degree));
         xd-=lspd*cos(glm::radians(degree));
         break;
     }
     case Qt::Key_Right:
     {
         degree -= 5.0f;
         break;
     }
     case Qt::Key_Left:
         degree += 5.0f;
         break;
     }
     paintGL();
}

void GLPP::paintGL()
{

    GLfloat triangle_vertex[] = {
        0.25f, 0.0f,
        -0.25f, -0.25f,
        -0.25f, 0.0f,
        -0.25f, 0.25f
    };
    GLfloat triangle_colors[] = {
        0.298f, 0.290f, 0.803f,
        0.764f, 0.752f, 0.866f,
        0.533f, 0.439f, 0.419f,
        0.764f, 0.752f, 0.866f
    };


    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(program);
    glClear(GL_COLOR_BUFFER_BIT);
    DrawPoints(100);
    mat4 rotationMatrix(1.0f);
    rotationMatrix= glm::translate(rotationMatrix, glm::vec3(xd, yd, 0.0f));
    rotationMatrix= glm::rotate(rotationMatrix, glm::radians(degree), glm::vec3(0.0f, 0.0f, 1.0f));





    GLuint location =glGetUniformLocation(program, "RotationMatrix");

    glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);




        GLuint *vboIds = new GLuint[2];
        glGenBuffers(2,
                     vboIds);


        attributeCoord2d = glGetAttribLocation( program, "coord2d");
        glBindBuffer( GL_ARRAY_BUFFER, vboIds[0]); // coordinates
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertex) * 8, triangle_vertex, GL_STATIC_DRAW);
        glVertexAttribPointer(attributeCoord2d, 2, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(attributeCoord2d);


        attributeColor = glGetAttribLocation( program, "color");
        glBindBuffer( GL_ARRAY_BUFFER, vboIds[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_colors) * 12, triangle_colors, GL_STATIC_DRAW);
        glVertexAttribPointer(attributeColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

        glEnableVertexAttribArray(attributeColor);



        glDrawArrays(
                     GL_TRIANGLE_FAN,
                     0,
                     4);
        createRegularPolygon(6);

        glDisableVertexAttribArray(attributeCoord2d);
        glDisableVertexAttribArray(attributeColor);
        update();
}
void GLPP::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
}
