#include "glpp.h"
#include <qmath.h>
#include <QVector2D>
#include <glm/glm.hpp>
#include <QImage>
using glm::mat4;
using glm::vec3;
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
GLPP::GLPP(QWidget *parent) : QOpenGLWidget(parent)
{

}

GLPP::~GLPP()
{

}


const char *vertexShader =
           "layout (location = 0) in vec3 position;\n"
           "layout (location = 1) in vec3 normal;\n"
           "layout (location = 2) in vec2 texCoord;\n"
           "out vec3 Normal;\n"
           "out vec3 FragPos;\n"           
           "out vec2 TexCoord;\n"
           "attribute vec3 color;\n"
           "varying vec3 vColor;\n"
           "uniform mat4 RotationMatrix;\n"
           "uniform mat4 frustum;\n"
           "uniform mat4 lookat;\n"
           "void main(void) {\n"
           "    gl_Position = frustum *lookat* RotationMatrix * vec4(position, 1.0f);\n"
           "    vColor = color;\n"
           "    TexCoord = texCoord;\n"
           "    FragPos = vec3(RotationMatrix * vec4(position, 1.0f));\n"
           "    Normal = vec3(RotationMatrix * vec4(normal,1.0f));\n"
           "}\n";

const char *fragmentShader=
        "struct Material {\n"
        "    vec3 ambient;\n"
        "    vec3 diffuse;\n"
        "    vec3 specular;\n"
        "    float shininess;\n"
        "};\n"
        "struct Light {\n"
        "    vec3 position;\n"
        "    vec3 ambient;\n"
        "    vec3 diffuse;\n"
        "    vec3 specular;\n"
        "    float constant;\n"
        "    float linear;\n"
        "    float quadratic;\n"
        "};\n"
        "in vec3 FragPos;\n"
        "in vec3 Normal;\n"
        "in vec2 TexCoord;\n"
        "uniform vec3 lightColor;\n"
        "uniform vec3 viewPos;\n"
        "uniform vec3 lightPos;\n"
        "uniform Material material;\n"
        "uniform Light light;\n"
        "varying vec3 vColor;\n"
        "uniform sampler2D ourTexture;\n"
        "void main(void) {\n"
        "   vec3 ambient = vColor * light.ambient * material.ambient;\n"
        "   vec3 norm = normalize(Normal);\n"
        "   vec3 lightDir = normalize(lightPos - FragPos);\n"
        "   float diff = max(dot(norm, lightDir), 0.0);\n"
        "   vec3 diffuse = vColor * light.diffuse * (diff * material.diffuse);\n"
        "   vec3 viewDir = normalize(viewPos - FragPos);\n"
        "   vec3 reflectDir = reflect(-lightDir, norm);\n"
        "   float distance = length(light.position - FragPos);\n"
        "   float coef = 1.0/(light.constant + light.linear * distance + light.quadratic *(distance * distance));\n"
        "   float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
        "   vec3 specular = vColor * light.specular * (spec * material.specular);\n"
        "   vec3 result = coef*(ambient + diffuse + specular);\n"
        "   gl_FragColor = texture2D(ourTexture,TexCoord) * vec4(result, 1.0);\n"
        " }\n";

GLint attributeCoord2d;
GLint attributeColor;
GLuint program;
GLfloat prevy1 = 0.0f,prevy2 = 0.0f,prevz1=0.0f,prevz2=0.0f;
GLfloat stage = 270.0f;
GLfloat degree=0.0f;
GLfloat tangle = 0.0f;
float xch=0.0f,zch=0.0f;;
GLfloat cubex = 5.0f, cubey = 5.0f;
GLfloat hcam = -1.0f, wcam = 0.0f;
GLfloat xd=0.0f, yd=0.0f, zd=0.0f;
GLfloat momentum = 0.0f;
GLfloat laststage = 0.0f;
GLuint texture[9];
GLfloat lft = -1.0f, rght = 1.0f, bottom = -1.0f,top = 1.0f,nr = 0.5f,fr = 30.0f;
bool is_f = false,is_b = false,is_l = false,is_r = false,is_fly = false,inside = true,run = false;
QTimer *timer;

void GLPP::UpdateEvent()
{
    float lspd = 0.05f;
    if(run)
        lspd*=3.0f;
    if(is_f)
    {
        if(!is_b)
        {
            if(inside)
            {
            if(yd+lspd*sin(glm::radians(degree))-0.5f>-cubey/2 && yd+lspd*sin(glm::radians(degree))+0.5f<cubey/2)
            {
                if(zd<1.0f)
                {
                    if (zd>0.1f)
                    {
                        if(xd<1.2f && xd>-1.2f)
                        {
                            if((yd +lspd*sin(glm::radians(degree))<-0.7f || yd +lspd*sin(glm::radians(degree))>0.7f))
                                yd+=lspd*sin(glm::radians(degree));
                        }
                        else
                            yd+=lspd*sin(glm::radians(degree));
                    }
                    else
                    {
                        if((xd<-0.8f && xd>-1.2f) || (xd<1.2f && xd>0.8f))
                        {
                            if((((yd +lspd*sin(glm::radians(degree))<0.3f)||(yd +lspd*sin(glm::radians(degree))>0.7f)) && ((yd +lspd*sin(glm::radians(degree))<-0.7f )||(yd +lspd*sin(glm::radians(degree))>-0.3f ))))
                                yd+=lspd*sin(glm::radians(degree));
                        }
                        else
                            yd+=lspd*sin(glm::radians(degree));
                    }
                }
            else
                yd+=lspd*sin(glm::radians(degree));
           }
           if(xd+lspd*cos(glm::radians(degree))-0.5f>-cubex/2 && xd+lspd*cos(glm::radians(degree))+0.5f<cubey/2)
           {
                if(zd<1.0f)
                {
                    if (zd>0.1f)
                    {
                        if(yd<0.7f && yd>-0.7f)
                        {
                            if((xd +lspd*cos(glm::radians(degree))<-1.2f || xd +lspd*cos(glm::radians(degree))>1.2f))
                                xd+=lspd*cos(glm::radians(degree));
                        }
                        else
                            xd+=lspd*cos(glm::radians(degree));
                    }
                    else
                    {
                        if((yd<-0.3f && yd>-0.7f) || (yd<0.7f && yd>0.3f))
                        {
                            if((((xd +lspd*cos(glm::radians(degree))<0.8f)||(xd +lspd*cos(glm::radians(degree))>1.2f)) && ((xd +lspd*cos(glm::radians(degree))<-1.2f )||(xd +lspd*cos(glm::radians(degree))>-0.8f ))))
                                xd+=lspd*cos(glm::radians(degree));
                        }
                        else
                            xd+=lspd*cos(glm::radians(degree));
                    }
                }
                else
                    xd+=lspd*cos(glm::radians(degree));
            }
            }
            else
            {
                if((yd + lspd*sin(glm::radians(degree)) < (cubey*7)/2-1.0f) && (yd + lspd*sin(glm::radians(degree)) > cubey/2))
                    if(xd>-cubex/2 && xd < cubex/2)
                    {
                        if(yd + lspd*sin(glm::radians(degree)) > cubey/2+0.5f)
                            yd+=lspd*sin(glm::radians(degree));
                    }
                    else
                        yd+=lspd*sin(glm::radians(degree));
                if((xd +lspd*cos(glm::radians(degree))<cubex*2-0.5f) && (xd +lspd*cos(glm::radians(degree))>-cubex+0.5f))
                xd+=lspd*cos(glm::radians(degree));
            }
            if(run)
                stage += 40.0f;
            else
                stage +=20.0f;
            if(stage>=360.0f)
            stage-=360.0f;
        }
    }
    if(is_b)
    {
        if(!is_f)
        {
            if(inside)
            {
            if(yd-lspd*sin(glm::radians(degree))-0.5f>-cubey/2 && yd-lspd*sin(glm::radians(degree))+0.5f<cubey/2)
            {
                if(zd<1.0f)
                {
                    if (zd>0.1f)
                    {
                        if(xd<1.2f && xd>-1.2)
                        {
                            if((yd -lspd*sin(glm::radians(degree))<-0.7f || yd -lspd*sin(glm::radians(degree))>0.7f))
                                yd-=lspd*sin(glm::radians(degree));
                        }
                        else
                            yd-=lspd*sin(glm::radians(degree));
                    }
                    else
                    {
                        if((xd<-0.8f && xd>-1.2f) || (xd<1.2f && xd>0.8f))
                        {
                            if((((yd -lspd*sin(glm::radians(degree))<0.3f)||(yd -lspd*sin(glm::radians(degree))>0.7f)) && ((yd -lspd*sin(glm::radians(degree))<-0.7f )||(yd -lspd*sin(glm::radians(degree))>-0.3f ))))
                                yd-=lspd*sin(glm::radians(degree));
                        }
                        else
                            yd-=lspd*sin(glm::radians(degree));
                    }
                }
                else
                    yd-=lspd*sin(glm::radians(degree));
            }
            if(xd-lspd*cos(glm::radians(degree))-0.5f>-cubex/2 && xd-lspd*cos(glm::radians(degree))+0.5f<cubey/2)
            {
                if(zd<1.0f)
                {
                    if (zd>0.1f)
                    {
                        if(yd<0.7f && yd>-0.7f)
                        {
                            if((xd -lspd*cos(glm::radians(degree))<-1.2f || xd -lspd*cos(glm::radians(degree))>1.2f))
                                xd-=lspd*cos(glm::radians(degree));
                        }
                        else
                            xd-=lspd*cos(glm::radians(degree));
                    }
                    else
                    {
                        if((yd<-0.3f && yd>-0.7f) || (yd<0.7f && yd>0.3f))
                        {
                            if((((xd -lspd*cos(glm::radians(degree))<0.8f)||(xd -lspd*cos(glm::radians(degree))>1.2f)) && ((xd -lspd*cos(glm::radians(degree))<-1.2f )||(xd -lspd*cos(glm::radians(degree))>-0.8f ))))
                                xd-=lspd*cos(glm::radians(degree));
                        }
                        else
                            xd-=lspd*cos(glm::radians(degree));
                    }
                }
                else
                    xd-=lspd*cos(glm::radians(degree));
            }
        }
        else
        {
                if((yd - lspd*sin(glm::radians(degree)) < (cubey*7)/2-1.0f) && (yd - lspd*sin(glm::radians(degree)) > cubey/2))
                    if(xd>-cubex/2 && xd < cubex/2)
                    {
                        if(yd - lspd*sin(glm::radians(degree)) > cubey/2+0.5f)
                            yd-=lspd*sin(glm::radians(degree));
                    }
                    else
                        yd-=lspd*sin(glm::radians(degree));
                if((xd -lspd*cos(glm::radians(degree))<cubex*2-0.5f) && (xd -lspd*cos(glm::radians(degree))>-cubex+0.5f))
                xd-=lspd*cos(glm::radians(degree));
        }
            if(run)
                stage -=40.0f;
            else
                stage -=20.0f;
            if(stage<=0.0f)
                stage+=360.0f;

        }
    }
    if(is_l)
    {
        if(!is_r)
        {
            degree += 10.0f;
        }
    }
    if(is_r)
    {
        if(!is_l)
        {
            degree -= 10.0f;
        }
    }
    if(is_fly)
    {
        if((yd > -0.7f) && (yd < 0.7f) && (xd > -1.2f) && (xd < 1.2f))
            {
            if((zd+momentum>0.1f) && (zd <= 0.1f))
                momentum = 0.0f;
            else
                if((zd + momentum < 1.0f) && (zd >=1.0f))
                {
                    momentum = 0.0f;
                    zd = 1.0f;
                }
            }
        if(zd+momentum>0)
            zd += momentum;
        else
        {
            zd = 0.0f;
            momentum = 0.0f;
            is_fly = false;
        }
        momentum -=0.02f;
    }
    paintGL();
}

struct GLPP::Body: protected QOpenGLFunctions
{
    float hfat,wfat,angle,begx,begy,begz,endx,endy,endz;
    Body* next,*prev;
    Body(float hf,float wf,float ang,float bx,float by,float bz,float ex,float ey,float ez,Body* begin)
    {
        hfat = hf;
        wfat = wf;
        angle = ang;
        begx = bx;
        begy = by;
        begz = bz;
        endx = ex;
        endy = ey;
        endz = ez;
        next = nullptr;
        prev = begin;
    }
    Body(float hf,float wf,float ang,float bx,float by,float bz,float ex,float ey,float ez,Body* begin,Body* end)
    {
        hfat = hf;
        wfat = wf;
        angle = ang;
        begx = bx;
        begy = by;
        begz = bz;
        endx = ex;
        endy = ey;
        endz = ez;
        next = end;
        prev = begin;
    }
    void Move(float dx,float dy,float dz)
    {
        if(next == nullptr)
        {
            float l = sqrt(glm::pow(endx-begx,2)+glm::pow(endy-begy,2)+glm::pow(endz-begz,2));
            float angxy = glm::atan((endx+dx-begx)/(endy+dy-begy));
            float angxz = glm::atan((endx+dx-begx)/(endz+dz-begz));
            float angyz = glm::atan((endy+dy-begy)/(endz+dz-begz));
            if(angxy==angxy&&angxz==angxz&&angyz==angyz)
            {
            endx = begx+sin(angxy)*sin(angxz)*l;
            endy = begy+sin(angyz)*cos(angxy)*l;
            endz = begz+cos(angyz)*cos(angxz)*l;
            }
        }
        else
        {
            float lp = sqrt(glm::pow((endx-begx),2)+glm::pow((endy-begy),2)+glm::pow((endz-begz),2));
            float ln = sqrt(glm::pow((next->endx-next->begx),2)+glm::pow((next->endy-next->begy),2)+glm::pow((next->endz-next->begz),2));
            float dl = sqrt(glm::pow((next->endx+dx-begx),2)+glm::pow((next->endy+dy-begy),2)+glm::pow((next->endz+dz-begz),2));
            float angxz = glm::atan((next->endx+dx-begx)/(next->endz+dz-begz));
            float lpyz = lp;
            float lnyz = ln;
            float dlyz = dl;
            if(angxz==angxz)
            {
            lpyz = cos(angxz)*lp;
            lnyz = cos(angxz)*ln;
            dlyz = cos(angxz)*dl;
            }
            float angyz = glm::atan((next->endy+dy-begy)/(next->endz+dz-begz));//(-pi/2;pi/2)
            if(angyz != angyz)
                angyz = 0.0f;
            float ddz = next->endz+dz-begz;
            float fang=0.0f,alf=0.0f,a=0.0f;
            if(ddz<0)
            {
                if(angyz < 0)
                {
                    a = (glm::pow(lnyz,2)+glm::pow(dlyz,2)-glm::pow(lpyz,2))/(2.0f*lnyz*dlyz);
                    alf = acos(a);//(0;pi)
                    if(alf!=alf)
                        alf=0.0f;
                    fang = alf + angyz;
                    endz = next->endz+dz+lnyz*cos(fang);
                    next->begz = endz;
                    endy = next->endy+dy+lnyz*sin(fang);
                    next->begy = endy;
                }
                else
                {
                    a =(glm::pow(lpyz,2)+glm::pow(dlyz,2)-glm::pow(lnyz,2))/(2.0f*lpyz*dlyz);
                    alf = acos(a);
                    if(alf!=alf)
                        alf=0.0f;
                    fang = alf - angyz;
                    endz = begz-lpyz*cos(fang);
                    next->begz = endz;
                    endy = begy+lpyz*sin(fang);
                    next->begy = endy;
                }
            }
            else
            {
                if(angyz < 0)
                {
                    a =(glm::pow(lpyz,2)+glm::pow(dlyz,2)-glm::pow(lnyz,2))/(2.0f*lpyz*dlyz);
                    alf = acos(a);
                    if(alf!=alf)
                        alf=0.0f;
                    fang = alf + angyz;
                    endz = begz+lpyz*cos(fang);
                    next->begz = endz;
                    endy = begy+lpyz*sin(fang);
                    next->begy = endy;
                }
                else
                {
                    a =(glm::pow(lpyz,2)+glm::pow(dlyz,2)-glm::pow(lpyz,2))/(2.0f*lpyz*dlyz);
                    alf = acos(a);
                    if(alf!=alf)
                        alf=0.0f;
                    fang = alf - angyz;
                    endz = next->endz+dz-lnyz*cos(fang);
                    next->begz = endz;
                    endy = next->endy+dy+lnyz*sin(fang);
                    next->begy = endy;
                }
            }
            next->endx +=dx;
            next->endy +=dy;
            next->endz +=dz;
            float somex = sqrt(glm::pow(lp,2)-glm::pow((endy-begy),2)-glm::pow(endz-begz,2));
            if(somex != somex)
                somex = 0.0f;
            else
            {
            if(next->endx>begx)
            {
                endx = begx+somex;//error
                next->begx = endx;
            }
            else
            {
                endx = begx-somex;//error
                next->begx = endx;
            }
            }
        }
    }
};
void GLPP::Draw(Body* b,float x,float y, float z)
{
    if(b->next!=nullptr)
        Draw(b->next,x,y,z);
    float l = sqrt(glm::pow(b->endx-b->begx,2)+glm::pow(b->endy-b->begy,2)+glm::pow(b->endz-b->begz,2));
    GLfloat polygon_vertex[48] =
    {
        -b->hfat/2,-b->wfat/2,0.0f,-1.0f,-1.0f,-1.0f,
        b->hfat/2,-b->wfat/2,0.0f,1.0f,-1.0f,-1.0f,
        b->hfat/2,b->wfat/2,0.0f,1.0f,1.0f,-1.0f,
        -b->hfat/2,b->wfat/2,0.0f,-1.0f,1.0f,-1.0f,
        -b->hfat/2,b->wfat/2,l,-1.0f,1.0f,1.0f,
        b->hfat/2,b->wfat/2,l,1.0f,1.0f,1.0f,
        b->hfat/2,-b->wfat/2,l,1.0f,-1.0f,1.0f,
        -b->hfat/2,-b->wfat/2,l,-1.0f,-1.0f,1.0f
    };
    GLfloat polygon_colors[24]
    {
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f
    };
    glUseProgram(program);

    GLuint aloc = glGetUniformLocation(program,"material.ambient"),dloc = glGetUniformLocation(program,"material.diffuse"),sloc = glGetUniformLocation(program,"material.specular"), shlac = glGetUniformLocation(program,"material.shininess");
    glUniform3f(aloc,0.2f,0.2f,0.2f);
    glUniform3f(dloc,0.6f,0.6f,0.6f);
    glUniform3f(sloc,0.02f,0.02f,0.02f);
    glUniform1f(shlac,1.0f);
    float xydeg,xzdeg,yzdeg;
    xydeg=glm::atan((b->begx-b->endx)/(b->begy-b->endy));
    xzdeg=glm::atan((b->begx-b->endx)/(b->begz-b->endz));
    yzdeg=glm::atan((b->begy-b->endy)/(b->begz-b->endz));
    mat4 rotationMatrix(1.0f);
    rotationMatrix= glm::translate(rotationMatrix, glm::vec3(xd, yd, zd));
    rotationMatrix= glm::rotate(rotationMatrix, glm::radians(degree-90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    rotationMatrix= glm::translate(rotationMatrix, glm::vec3(x+b->begx, y+b->begy, z+b->begz));
    if(xydeg==xydeg)
    rotationMatrix= glm::rotate(rotationMatrix, xydeg, glm::vec3(0.0f, 0.0f, 1.0f));
    if(xzdeg==xzdeg)
    rotationMatrix= glm::rotate(rotationMatrix, xzdeg, glm::vec3(0.0f, 1.0f, 0.0f));
    if(yzdeg==yzdeg)
    rotationMatrix= glm::rotate(rotationMatrix, yzdeg, glm::vec3(1.0f, 0.0f, 0.0f));
    GLuint location = glGetUniformLocation(program, "RotationMatrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);

    unsigned int vertex_query[8] = {6,7,5,4,2,3,1,0},vertex_query1[8] = {4,3,7,0,6,1,5,2};

    GLuint *vboIds = new GLuint[3];
    glGenBuffers(3,
                 vboIds);

    glBindBuffer( GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * 48, polygon_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * 48, polygon_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    attributeColor = glGetAttribLocation( program, "color");
    glEnableVertexAttribArray(attributeColor);
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_colors) * 24, polygon_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawElements(GL_QUAD_STRIP,8,GL_UNSIGNED_INT,vertex_query);
    glDrawElements(GL_QUAD_STRIP,8,GL_UNSIGNED_INT,vertex_query1);


    glDisableVertexAttribArray(attributeColor);
}
void GLPP::Draw(Body* b,unsigned int numb)
{
    float l = sqrt(glm::pow(b->endx-b->begx,2)+glm::pow(b->endy-b->begy,2)+glm::pow(b->endz-b->begz,2));
    GLfloat polygon_vertex[48] =
    {
        -b->hfat/2,-b->wfat/2,0.0f,-1.0f,-1.0f,-1.0f,
        b->hfat/2,-b->wfat/2,0.0f,1.0f,-1.0f,-1.0f,
        b->hfat/2,b->wfat/2,0.0f,1.0f,1.0f,-1.0f,
        -b->hfat/2,b->wfat/2,0.0f,-1.0f,1.0f,-1.0f,
        -b->hfat/2,b->wfat/2,l,-1.0f,1.0f,1.0f,
        b->hfat/2,b->wfat/2,l,1.0f,1.0f,1.0f,
        b->hfat/2,-b->wfat/2,l,1.0f,-1.0f,1.0f,
        -b->hfat/2,-b->wfat/2,l,-1.0f,-1.0f,1.0f
    };
    GLfloat polygon_colors[24]
    {
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f,
        0.7f,0.7f,0.7f
    };
    GLfloat tex_vertex[16] =
    {
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        1.0f,0.0f,
        0.0f,0.0f
    };
    GLfloat tex_vertex1[16] =
    {
        1.0f,0.0f,
        0.0f,0.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        0.0f,1.0f,
        1.0f,1.0f
    };
    GLfloat tex_vertex2[16] =
    {
        0.0f,0.0f,
        1.0f,0.0f,
        0.0f,0.0f,
        1.0f,0.0f,
        1.0f,1.0f,
        0.0f,1.0f,
        1.0f,1.0f,
        0.0f,1.0f
    };
    glUseProgram(program);

    GLuint aloc = glGetUniformLocation(program,"material.ambient"),dloc = glGetUniformLocation(program,"material.diffuse"),sloc = glGetUniformLocation(program,"material.specular"), shlac = glGetUniformLocation(program,"material.shininess");
    glUniform3f(aloc,0.2f,0.2f,0.2f);
    glUniform3f(dloc,0.6f,0.6f,0.6f);
    glUniform3f(sloc,0.02f,0.02f,0.02f);
    glUniform1f(shlac,1.0f);
    float xydeg,xzdeg,yzdeg;
    xydeg=glm::atan((b->begx-b->endx)/(b->begy-b->endy));
    xzdeg=glm::atan((b->begx-b->endx)/(b->begz-b->endz));
    yzdeg=glm::atan((b->begy-b->endy)/(b->begz-b->endz));
    mat4 rotationMatrix(1.0f);
    rotationMatrix= glm::translate(rotationMatrix, glm::vec3(b->begx, b->begy, b->begz));
    if(xydeg==xydeg)
    rotationMatrix= glm::rotate(rotationMatrix, xydeg, glm::vec3(0.0f, 0.0f, 1.0f));
    if(xzdeg==xzdeg && xydeg==xydeg)
    rotationMatrix= glm::rotate(rotationMatrix, xzdeg, glm::vec3(-sin(xydeg), cos(xydeg), 0.0f));
    if(yzdeg==yzdeg && xydeg==xydeg && xzdeg==xzdeg)
    rotationMatrix= glm::rotate(rotationMatrix, yzdeg, glm::vec3(cos(xydeg)*cos(xzdeg), sin(xydeg), -sin(xzdeg)));
    GLuint location = glGetUniformLocation(program, "RotationMatrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);

    unsigned int vertex_query[8] = {6,7,4,5,3,2,1,0},vertex_query1[8] = {4,3,0,7,1,6,5,2},vertex_query2[8] = {5,4,3,2,0,1,6,7};

    GLuint *vboIds = new GLuint[4];
    glGenBuffers(4,
                 vboIds);

    glBindBuffer( GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * 48, polygon_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * 48, polygon_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_vertex) * 16, tex_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,0, 0);
    glEnableVertexAttribArray(2);


    attributeColor = glGetAttribLocation( program, "color");
    glEnableVertexAttribArray(attributeColor);
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_colors) * 24, polygon_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeColor, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindTexture(GL_TEXTURE_2D, texture[numb]);

    glDrawElements(GL_QUADS,8,GL_UNSIGNED_INT,vertex_query);

    glBindBuffer( GL_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_vertex1) * 16, tex_vertex1, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,0, 0);
    glEnableVertexAttribArray(2);

    glDrawElements(GL_QUADS,8,GL_UNSIGNED_INT,vertex_query1);

    glBindBuffer( GL_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(tex_vertex2) * 16, tex_vertex2, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,0, 0);
    glEnableVertexAttribArray(2);

    glDrawElements(GL_QUADS,8,GL_UNSIGNED_INT,vertex_query2);

    glDisableVertexAttribArray(attributeColor);
}
struct GLPP::Dog
{
    float cx,cy,cz;
    Body* parts[6];
    Body* main;
    Dog(float centerx,float centery,float centerz)
    {
        cx=centerx;
        cy=centery;
        cz=centerz;
        main = new Body(0.2f,0.18f,0.0f,0.0f,-0.5f,0.8f,0.0f,0.5f,0.8f,nullptr);
        Body* rfleg = new Body(0.06f,0.12f,0.0f,0.1f,0.55f,0.25f,0.1f,0.4f,0.0f,nullptr);
        Body* lfleg = new Body(0.06f,0.12f,0.0f,-0.1f,0.55f,0.25f,-0.1f,0.4f,0.0f,nullptr);
        Body* rbleg = new Body(0.04f,0.08f,0.0f,0.1f,-0.25f,0.25f,0.1f,-0.4f,0.0f,nullptr);
        Body* lbleg = new Body(0.04f,0.08f,0.0f,-0.1f,-0.25f,0.25f,-0.1f,-0.4f,0.0f,nullptr);
        parts[0]=new Body(0.08f,0.14f,0.0f,0.1f,0.4f,0.5f,0.1f,0.55f,0.25f,nullptr,rfleg); //front right
        parts[1]=new Body(0.08f,0.14f,0.0f,-0.1f,0.4f,0.5f,-0.1f,0.55f,0.25f,nullptr,lfleg); //front left
        parts[2]=new Body(0.1f,0.16f,0.0f,-0.1f,-0.4f,0.5f,-0.1f,-0.25f,0.25f,nullptr,lbleg); //back left
        parts[3]=new Body(0.1f,0.16f,0.0f,0.1f,-0.4f,0.5f,0.1f,-0.25f,0.25f,nullptr,rbleg);//back right
        parts[4]=new Body(0.16f,0.2f,0.0f,0.0f,0.45f,0.9f,0.0f,0.7f,0.9f,nullptr);//head
        parts[5]=new Body(0.08f,0.08f,0.0f,0.0f,-0.5f,0.85f,0.0f,-0.5f,1.15f,nullptr);//tail
    }
    void Move(int numb, float x,float y,float z)
    {
        parts[numb]->Move(x,y,z);
    }
};
void GLPP::DrawDog(Dog* d)
{
    if(d->main!=nullptr)
    Draw(d->main,d->cx,d->cy,d->cz);
    for(int i =0;i<6;i++)
    {
        if(d->parts[i]!=nullptr)
        Draw(d->parts[i],d->cx,d->cy,d->cz);
    }
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
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.6f, 0.6f, 0.8f, 1.0f);
    timer = new QTimer();
    timer->start(40);
    connect(timer,&QTimer::timeout,this,[=](){UpdateEvent();});
    k9 = new Dog(0.0f,0.0f,-2.1f);
    glGenTextures(9, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img0(QImage(QString(":/textures/floor.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img0.width(),img0.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img0.bits());
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img1(QImage(QString(":/textures/wood.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img1.width(),img1.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img1.bits());
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img2(QImage(QString(":/textures/table.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2.width(),img2.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img2.bits());
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img3(QImage(QString(":/textures/calendar.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img3.width(),img3.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img3.mirrored().bits());
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img4(QImage(QString(":/textures/leg.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img4.width(),img4.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img4.bits());
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img5(QImage(QString(":/textures/door.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img5.width(),img5.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img5.mirrored().bits());
    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img6(QImage(QString(":/textures/fance.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img6.width(),img6.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img6.mirrored().bits());
    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img7(QImage(QString(":/textures/snow.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img7.width(),img7.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img7.bits());
    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    QImage img8(QImage(QString(":/textures/forest.jpg")));
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img8.width(),img8.height(),0,GL_BGRA,GL_UNSIGNED_BYTE,img8.mirrored().bits());
}

void GLPP::createRoom(GLfloat x, GLfloat y,GLfloat z, GLfloat dx, GLfloat dy, GLfloat dz,GLfloat r,GLfloat g,GLfloat b,int set)
{
    float scale1,scale2,scale3;
    if(set == 0)
    {
        scale1 = 2.0f;
        scale2 = 3.0f;
        scale3=1.0f;
    }
    if(set == 1)
    {
        scale1 = 10.0f;
        scale2 = 1.0f;
        scale3 = 6.0f;
    }
    if(set == 2)
    {
        scale1 = 10.0f;
        scale2 = 1.0f;
        scale3 = 2.0f;
    }
    GLfloat polygon_vertex[64] =
    {
        x,y,z,1.0f,1.0f,1.0f,0.0f,0.0f,
        (x+dx),y,z,-1.0f,1.0f,1.0f,scale3,0.0f,
        (x+dx),(y+dy),z,-1.0f,-1.0f,1.0f,0.0f,0.0f,
        x,(y+dy),z,1.0f,-1.0f,1.0f,scale3,0.0f,
        x,(y+dy),(z+dz),1.0f,-1.0f,-1.0f,scale3,scale2,
        (x+dx),(y+dy),(z+dz),-1.0f,-1.0f,-1.0f,0.0f,scale2,
        (x+dx),y,(z+dz),-1.0f,1.0f,-1.0f,scale3,scale2,
        x,y,(z+dz),1.0f,1.0f,-1.0f,0.0f,scale2
    };
    GLfloat floor_vert[] =
    {
        0.0f,0.0f,
        scale1,0.0f,
        scale1,scale1,
        0.0f,scale1
    };
    GLfloat text_vert[]=
    {
        0.0f,0.0f,
        scale3,0.0f,
        scale3,0.0f,
        0.0f,0.0f,
        0.0f,scale2,
        scale3,scale2,
        scale3,scale2,
        0.0f,scale2
    };
    GLfloat polygon_colors[24]
    {
        r,g,b,
        r,g,b,
        r,g,b,
        r,g,b,
        r,g,b,
        r,g,b,
        r,g,b,
        r,g,b
    };
    unsigned int vertex_query[4] = {0,1,2,3},vertex_query1[8] = {2,5,6,1,0,7,4,3},vertex_query2[8] = {3,2,5,4,1,6,7,0};
    glUseProgram(program);


    GLuint *vboIds = new GLuint[6];
    glGenBuffers(6,
                 vboIds);

    glBindBuffer( GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * 64, polygon_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * 64, polygon_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_vertex) * 64, polygon_vertex, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);


     glEnableVertexAttribArray(attributeColor);
    attributeColor = glGetAttribLocation( program, "color");
    glBindBuffer( GL_ARRAY_BUFFER, vboIds[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(polygon_colors) * 24, polygon_colors, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeColor, 3, GL_FLOAT, GL_FALSE, 0, 0);

    mat4 rotationMatrix(1.0f);
    GLuint location = glGetUniformLocation(program, "RotationMatrix");
    glUniformMatrix4fv(location, 1, GL_FALSE, &rotationMatrix[0][0]);

    if(set == 0)
        glBindTexture(GL_TEXTURE_2D, texture[1]);
    if(set == 1)
        glBindTexture(GL_TEXTURE_2D, texture[6]);
    if(set == 2)
        glBindTexture(GL_TEXTURE_2D, texture[8]);
    glDrawElements(GL_QUADS,8,GL_UNSIGNED_INT,vertex_query1);

    glBindBuffer( GL_ARRAY_BUFFER, vboIds[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floor_vert) * 8, floor_vert, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    if(set == 0)
        glBindTexture(GL_TEXTURE_2D, texture[0]);
    if(set == 1)
        glBindTexture(GL_TEXTURE_2D, texture[7]);
    if(set == 2)
        glBindTexture(GL_TEXTURE_2D, texture[7]);
    glDrawElements(GL_QUADS,4,GL_UNSIGNED_INT,vertex_query);

    glBindBuffer( GL_ARRAY_BUFFER, vboIds[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text_vert) * 16, text_vert, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(2);

    if(set == 0)
        glBindTexture(GL_TEXTURE_2D, texture[1]);
    if(set == 1)
        glBindTexture(GL_TEXTURE_2D, texture[6]);
    if(set == 2)
        glBindTexture(GL_TEXTURE_2D, texture[8]);
    glDrawElements(GL_QUADS,8,GL_UNSIGNED_INT,vertex_query2);
    glBindTexture(GL_TEXTURE_2D, texture[1]);

    glDisableVertexAttribArray(attributeColor);
}

void GLPP::keyPressEvent(QKeyEvent *event)
{
     switch (event->key())
     {
     case Qt::Key_Escape:
     {
         close();
         break;
     }
     case Qt::Key_Shift:
     {
         if(!run)
             run = true;
         break;
     }
     case Qt::Key_Space:
     {
         if(!is_fly || zd == 1.0f)
         {
             momentum = 0.2f;
             is_fly = true;
         }
         break;
     }
     case Qt::Key_F:
     {
         if(yd>cubey/2-0.6f && yd<cubey/2+0.6f && xd<-0.5f && xd>-1.5f)
         {
             if(inside)
             {
                 yd+=1.2f;
                inside =!inside;
             }
             else
             {
                 yd-=1.2f;
                 inside =!inside;
             }
         }
         break;
     }
     case Qt::Key_W:
     {
         if(hcam<cubey/2-0.8f)
         hcam+=0.1f;
         break;
     }
     case Qt::Key_S:
     {
         if(hcam>-cubey/2+0.8f)
         hcam-=0.1f;
         break;
     }
     case Qt::Key_A:
     {
         if(wcam>-cubex/2+0.8f)
         wcam-=0.1f;
         break;
     }
     case Qt::Key_D:
     {
         if(wcam<cubex/2-0.8f)
         wcam+=0.1f;
         break;
     }
     case Qt::Key_Up:
     {
         if(!is_f)
             is_f=true;
         break;
     }
     case Qt::Key_Down:
     {
         if(!is_b)
             is_b=true;
         break;
     }
     case Qt::Key_Right:
     {
         if(!is_r)
             is_r=true;
         break;
     }
     case Qt::Key_Left:
     {
         if(!is_l)
             is_l=true;
         break;
     }
     }
}
void GLPP::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Shift:
    {
        if(run)
            run = false;
        break;
    }
    case Qt::Key_Up:
    {
        if(is_f)
            is_f=false;
        break;
    }
    case Qt::Key_Down:
    {
        if(is_b)
            is_b=false;
        break;
    }
    case Qt::Key_Right:
    {
        if(is_r)
            is_r=false;
        break;
    }
    case Qt::Key_Left:
    {
        if(is_l)
            is_l=false;
        break;
    }
    }
}

void GLPP::paintGL()
{
    glUseProgram(program);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        GLuint Lookatloc = glGetUniformLocation(program,"lookat");
        vec3 campos,up,centerpos;
        if(inside)
        {
            campos = vec3(wcam,hcam,0.2f);
            centerpos = vec3(xd,yd,zd-2.1f);
            up = glm::normalize(vec3(0.0f,0.0f,1.0f));
        }
        else
        {
            campos = vec3(-2.0f,cubey/2+2.0f,1.0f);
            centerpos = vec3(xd,yd,zd-2.1f);
            up = glm::normalize(vec3(0.0f,0.0f,1.0f));
        }
        mat4 lookat = glm::lookAt(campos,centerpos,up);
        glUniformMatrix4fv(Lookatloc, 1, false, &lookat[0][0]);
        GLuint uMatrixLocation = glGetUniformLocation(program,"frustum");
        mat4 Proj;
        Proj = glm::frustum(lft, rght, bottom, top, nr, fr);
        glUniformMatrix4fv(uMatrixLocation, 1, false, &Proj[0][0]);
        GLint conloc = glGetUniformLocation(program, "light.constant");
        GLint linloc = glGetUniformLocation(program, "light.linear");
        GLint quadloc = glGetUniformLocation(program, "light.quadratic");
        if(inside)
        {
            glUniform1f(conloc, 0.1f);
            glUniform1f(linloc, 0.2f);
            glUniform1f(quadloc, 0.2f);
        }
        else
        {
            glUniform1f(conloc, 0.8f);
            glUniform1f(linloc, 0.0f);
            glUniform1f(quadloc, 0.0f);
        }
        GLint viewPosLoc = glGetUniformLocation(program, "viewPos");
        if(inside)
        glUniform3f(viewPosLoc, wcam, hcam,0.5f );
        else
            glUniform3f(viewPosLoc, -2.0f, cubey/2+2.0f,1.0f );
        GLint lightPosLoc = glGetUniformLocation(program, "lightPos");
        if(inside)
            glUniform3f(lightPosLoc, 0.0f, 0.0f, 0.0f);
        else
            glUniform3f(lightPosLoc, 0.0f, cubey*3, 2.0f);
        GLint lightcolorLoc = glGetUniformLocation(program, "lightColor");
        glUniform3f(lightcolorLoc, 1.0f, 1.0f, 1.0f);
        GLuint aloc = glGetUniformLocation(program,"material.ambient"),dloc = glGetUniformLocation(program,"material.diffuse"),sloc = glGetUniformLocation(program,"material.specular"), shlac = glGetUniformLocation(program,"material.shininess");
        glUniform3f(aloc,0.2f,0.2f,0.2f);
        glUniform3f(dloc,0.6f,0.6f,0.6f);
        glUniform3f(sloc,0.1f,0.1f,0.1f);
        glUniform1f(shlac,1.0f);
        GLuint loca = glGetUniformLocation(program,"light.ambient"),locd = glGetUniformLocation(program,"light.diffuse"),locs = glGetUniformLocation(program,"light.specular"),locp = glGetUniformLocation(program,"light.position");
        if(inside)
        {
            glUniform3f(loca,1.0f,0.5f,0.0f);
            glUniform3f(locd,1.0f,0.5f,0.0f);
        }
        else
        {
            glUniform3f(loca,0.8f,0.8f,1.0f);
            glUniform3f(locd,0.8f,0.8f,1.0f);
        }
        glUniform3f(locs,1.0f,1.0f,1.0f);
        if(inside)
            glUniform3f(locp,0.0f,0.0f,0.0f);
        else
            glUniform3f(lightPosLoc, 0.0f, cubey*2, 2.0f);
        createRoom(-cubex/2,-cubey/2,-2.1f,cubex,cubey,4.0f,0.8f,0.8f,0.82f,0);
        if(!inside)
        {
            createRoom(-cubex,cubey/2-0.5f,-2.1f,3*cubex,cubey*3,1.8f,0.8f,0.8f,0.82f,1);
            createRoom(-cubex*3,-cubey,-2.2f,7*cubex,cubey*6,16.0f,0.8f,0.8f,0.82f,2);
        }
        if(stage != laststage)
        {
        float dy1 = 0.1f*sin(glm::radians(stage)),dy2 = -0.1f*sin(glm::radians(stage)),dz1 = 0.1f*cos(glm::radians(stage)),dz2 = -0.1f*cos(glm::radians(stage));
        if(dz1<=0.0f)
            dz1 = 0.0f;
        if(dz2<=0.0f)
            dz2 = 0.0f;
        dy1 = dy1 - prevy1;
        dy2 = dy2 - prevy2;
        dz1 = dz1 - prevz1;
        dz2 = dz2 - prevz2;
        prevy1 = 0.1f*sin(glm::radians(stage));
        prevy2 = -0.1f*sin(glm::radians(stage));
        prevz1 = 0.1f*cos(glm::radians(stage));
        prevz2 = -0.1f*cos(glm::radians(stage));
        if(prevz1<=0.0f)
            prevz1 = 0.0f;
        if(prevz2<=0.0f)
            prevz2 = 0.0f;
        k9->Move(0,0.0f,dy1,dz1);
        k9->Move(1,0.0f,dy2,dz2);
        k9->Move(2,0.0f,dy1,dz1);
        k9->Move(3,0.0f,dy2,dz2);
        }
        tangle += 10.0f;
        if (tangle >= 360.0f)
            tangle = 0.0f;
        float curx = 0.1f*sin(glm::radians(tangle)) - xch,curz = 0.1f*cos(glm::radians(tangle)) - zch;
        xch = 0.1f*sin(glm::radians(tangle));
        zch = 0.1f*cos(glm::radians(tangle));
        k9->Move(5,curx,0.0f,curz);
        laststage = stage;
        DrawDog(k9);
        Body *table = new Body(1.0f,0.1f,0.0f,-1.0f,0.0f,-1.0f,1.0f,0.0f,-1.0f,nullptr);
        Body *legs[4];
        legs[0] = new Body(0.14f,0.14f,0.0f,-0.93f,-0.43f,-2.1f,-0.93f,-0.43f,-1.05f,nullptr);
        legs[1] = new Body(0.14f,0.14f,0.0f,0.93f,-0.43f,-2.1f,0.93f,-0.43f,-1.05f,nullptr);
        legs[2] = new Body(0.14f,0.14f,0.0f,0.93f,0.43f,-2.1f,0.93f,0.43f,-1.05f,nullptr);
        legs[3] = new Body(0.14f,0.14f,0.0f,-0.93f,0.43f,-2.1f,-0.93f,0.43f,-1.05f,nullptr);
        for(int i = 0;i<4;i++)
            Draw(legs[i],4);
        Draw(table,2);
        Body *calendar = new Body(0.5f,0.04f,0.0f,0.2f,cubey/2-0.05f,-0.6f,0.2f,cubey/2-0.05f,-1.2f,nullptr);
        Draw(calendar,3);
        Body *door = new Body(1.0f,0.4f,0.0f,-1.0f,cubey/2,-2.1f,-1.0f,cubey/2,-0.1f,nullptr);
        Draw(door,5);

    update();
}
void GLPP::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
}
