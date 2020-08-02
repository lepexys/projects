#include <windows.h>
#define WIN32_LEAN_AND_MEAN 1
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>
#include "glext.h"
#include "wglext.h"
#pragma comment(lib, "opengl32.lib")
#define UPDATE_TIMER_ID 200

    static HDC hDC;
    static HGLRC hRC;
    static char* windowClassName = "OpenGLApplication";
    static char* windowTitleName = "OpenGL Application";
    static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;
    static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
    static BOOL keys[256];

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

void DrawStar(GLfloat x,GLfloat y,GLfloat z,GLfloat l,GLfloat a, GLint k)
{
    GLint i = 0;
    glTranslatef(x,y,z);
    glRotatef(a,0.0f,0.0f,1.0f);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f,1.0f,0.2f);
    glVertex3f(0.0f,0.0f,0.0f);
    while(i<k)
    {
        glVertex3f(l*cos((360/k)*i),l*sin((360/k)*i),0.0f);
        glVertex3f(0.15f*cos((360/(k*2))*(i*2+1)),0.15f*sin((360/(k*2))*(i*2+1)),0.0f);
        i++;
    }
    glVertex3f(l,0.0f,0.0f);
    glEnd();
    glRotatef(-a,0.0f,0.0f,1.0f);
    glTranslatef(-x,-y,-z);
}
void DrawBox3(GLfloat x,GLfloat y,GLfloat z,GLfloat xl,GLfloat yl,GLfloat zl,GLfloat r, GLfloat g,GLfloat b )
{
    GLfloat xm=x+xl, ym=y+yl, zm=z+zl;
    glBegin(GL_QUADS);
    glColor3f(r,g,b); glVertex3f(x,y,zm);
    glColor3f(r,g,b); glVertex3f(xm,y,zm);
    glColor3f(r,g,b); glVertex3f(xm,ym,zm);
    glColor3f(r,g,b); glVertex3f(x,ym,zm);
    //
    glColor3f(r,g,b); glVertex3f(x,y,z);
    glColor3f(r,g,b); glVertex3f(xm,y,z);
    glColor3f(r,g,b); glVertex3f(xm,ym,z);
    glColor3f(r,g,b); glVertex3f(x,ym,z);
    //
    glColor3f(r,g,b); glVertex3f(x,y,z);
    glColor3f(r,g,b); glVertex3f(x,y,zm);
    glColor3f(r,g,b); glVertex3f(xm,y,zm);
    glColor3f(r,g,b); glVertex3f(xm,y,z);
    //
    glColor3f(r,g,b); glVertex3f(x,ym,z);
    glColor3f(r,g,b); glVertex3f(x,ym,zm);
    glColor3f(r,g,b); glVertex3f(xm,ym,zm);
    glColor3f(r,g,b);glVertex3f(xm,ym,z);
    //
    glColor3f(r,g,b); glVertex3f(x,y,zm);
    glColor3f(r,g,b); glVertex3f(x,ym,zm);
    glColor3f(r,g,b); glVertex3f(x,ym,z);
    glColor3f(r,g,b); glVertex3f(x,y,z);
    //
    glColor3f(r,g,b); glVertex3f(xm,y,zm);
    glColor3f(r,g,b); glVertex3f(xm,ym,zm);
    glColor3f(r,g,b); glVertex3f(xm,ym,z);
    glColor3f(r,g,b); glVertex3f(xm,y,z);
    //
    glEnd();
}
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f, alpha = 0.0f;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
    {
        MessageBox(0,"Ошибка регистрации класса окна","Ошибка",MB_OK|MB_ICONERROR);
        return FALSE;
    }

    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
                          WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT,
                          CW_USEDEFAULT,
                          640,
                          480,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);
    if(!hwnd)
    {
    MessageBox(0,"Ошибка создания окна.",
    "Ошибка",MB_OK|MB_ICONERROR);
    return FALSE;
    }
    ShowWindow(hwnd, nCmdShow);
    EnableOpenGL(hwnd, &hDC, &hRC);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f,5.0f,0.0f,5.0f,0.0f,10.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    while (!bQuit)
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {
            glClearColor(1.0f,1.0f,1.0f,0.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glPushMatrix();
            DrawBox3(1.2f,0.1f,-2.6f,0.4f,0.12f,2.0f,0.1f,0.0f,0.2f);//foot left
            DrawBox3(1.8f,0.1f,-2.6f,0.4f,0.12f,2.0f,0.1f,0.0f,0.2f);// fool right
            DrawBox3(1.4f,0.2f,-2.6f,0.2f,0.7f,2.0f,0.15f,0.0f,0.4f);// low leg left
            DrawBox3(1.8f,0.2f,-2.6f,0.2f,0.7f,2.0f,0.15f,0.0f,0.4f);//low leg right
            DrawBox3(1.35f,0.9f,-2.6f,0.25f,1.2f,2.0f,0.2f,0.0f,0.7f);// high leg left
            DrawBox3(1.8f,0.9f,-2.6f,0.25f,1.2f,2.0f,0.2f,0.0f,0.7f);// high leg right
            DrawBox3(1.35f,2.1f,-2.6f,0.7f,0.4f,2.0f,0.2f,0.0f,0.7f);// pipi
            DrawBox3(1.35f,2.5f,-2.6f,0.7f,0.6f,2.0f,0.2f,0.0f,0.6f);// belly
            DrawBox3(1.25f,3.1f,-2.6f,0.9f,0.6f,2.0f,0.15f,0.0f,0.5f);// chest
            DrawBox3(1.55f,3.7f,-2.6f,0.3f,0.45f,2.0f,0.2f,0.0f,0.7f);// head
            DrawBox3(1.525f,4.05f,-2.5f,0.35f,0.16f,2.0f,0.8f,0.7f,0.0f);// circlet
            DrawBox3(1.65f,4.05f,-2.45f,0.1f,0.16f,2.0f,0.1f,0.1f,0.0f);//backle
            DrawBox3(1.67f,4.07f,-2.4f,0.06f,0.12f,2.0f,0.8f,0.7f,0.0f);//thing
            glTranslatef(1.65f,4.2f,0.0f);
            glRotatef(15.0f,0.0f,0.0f,1.0f);
            DrawBox3(-0.12f,-0.14f,-2.7f,0.3f,0.4f,2.0f,0.05f,0.0f,0.1f);//hair
            glRotatef(-15.0f,0.0f,0.0f,1.0f);
            glTranslatef(0.1f,0.0f,0.0f);
            glRotatef(-15.0f,0.0f,0.0f,1.0f);
            DrawBox3(-0.2f,-0.14f,-2.7f,0.32f,0.4f,2.0f,0.05f,0.0f,0.1f);// another hair
            glRotatef(15.0f,0.0f,0.0f,1.0f);
            glTranslatef(-1.75f,-4.1f,0.0f);
            glTranslatef(1.25f,3.45f,0.0f);
            glRotatef(65.0f,0.0f,0.0f,1.0f);
            DrawBox3(-0.6f,-0.2f,-2.6f,0.8f,0.3f,2.0f,0.2f,0.0f,0.7f);// left arm1
            glRotatef(-65.0f,0.0f,0.0f,1.0f);
            glTranslatef(-1.25f,-3.45f,0.0f);
            glTranslatef(1.12f,3.0f,0.0f);
            glRotatef(-50.0f,0.0f,0.0f,1.0f);
            DrawBox3(-0.1f,-0.2f,-2.6f,0.8f,0.2f,2.0f,0.2f,0.0f,0.7f);//left arm2
            glRotatef(50.0f,0.0f,0.0f,1.0f);
            glTranslatef(-1.12f,-3.0f,0.0f);
            glTranslatef(2.1f,3.45f,0.0f);
            glRotatef(-75.0f,0.0f,0.0f,1.0f);
            DrawBox3(-0.2f,-0.2f,-2.6f,0.8f,0.3f,2.0f,0.2f,0.0f,0.7f);//right arm1
            glRotatef(75.0f,0.0f,0.0f,1.0f);
            glTranslatef(-2.1f,-3.45f,0.0f);
            DrawBox3(2.08f,2.8f,-2.5f,0.25f,0.3f,2.0f,0.15f,0.0f,0.6f);//right arm2
            DrawStar(2.1f,2.9,-0.4f,1.0f,theta * 7,6);
            glPopMatrix();
            SwapBuffers(hDC);
            theta += 1.0f;
            alpha = 15.0f * sin(theta);
            Sleep (40);
        }
    }
    DisableOpenGL(hwnd, hDC, hRC);
    DestroyWindow(hwnd);
    return msg.wParam;
}



void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    static PIXELFORMATDESCRIPTOR pfd;

    int iFormat;
    *hDC = GetDC(hwnd);
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 24;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(hDC, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void InitOpenGLExt(HWND _hWnd) {
auto hDC = GetDC(_hWnd);
PIXELFORMATDESCRIPTOR _pfd = { 0 };
_pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
_pfd.dwFlags = PFD_DRAW_TO_WINDOW |
PFD_SUPPORT_OPENGL |
PFD_DOUBLEBUFFER;
_pfd.iLayerType = PFD_MAIN_PLANE;
_pfd.iPixelType = PFD_TYPE_RGBA;
_pfd.cDepthBits = 24;
_pfd.cColorBits = 24;
_pfd.cAlphaBits = 8;
_pfd.nVersion = 1;
auto _pixelFormat = ChoosePixelFormat(hDC, &_pfd);
SetPixelFormat(hDC, _pixelFormat, &_pfd);
auto _hrcFake = wglCreateContext(hDC);
wglMakeCurrent(hDC, _hrcFake);
wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)
wglGetProcAddress("wglChoosePixelFormatARB");
wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)
wglGetProcAddress("wglCreateContextAttribsARB");
wglMakeCurrent(NULL, NULL);
wglDeleteContext(_hrcFake);
}

void InitScene() {
glClearColor(0.25f, 1.0f, 0.25f, 0.0f);
}

void Reshape(GLsizei _width, GLsizei _height, GLint _x, GLint _y) {
if (!_height)
return;
glViewport(_x, _y, _width, _height);
}

void DrawScene(DWORD _elapsedTime) {
glClear(GL_COLOR_BUFFER_BIT);
}

void CALLBACK DrawTimer(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
DrawScene(dwTime);
SwapBuffers(hDC);
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
switch (message)
{
case WM_ACTIVATE:
switch (LOWORD(wParam))
{
case WA_ACTIVE:
case WA_CLICKACTIVE:
SetTimer(hWnd, UPDATE_TIMER_ID, 100,
(TIMERPROC)&DrawTimer);
break;
case WA_INACTIVE:
KillTimer(hWnd, UPDATE_TIMER_ID);
break;
default:
return DefWindowProc(hWnd, message, wParam, lParam);
}
break;
case WM_KEYDOWN:
keys[wParam] = TRUE;
if (wParam == VK_ESCAPE)
DestroyWindow(hWnd);
break;
case WM_KEYUP:
keys[wParam] = FALSE;
break;
case WM_SIZE:
Reshape(LOWORD(lParam), HIWORD(lParam),0,0);
break;
case WM_DESTROY:
case WM_CLOSE:
KillTimer(hWnd, UPDATE_TIMER_ID);
ChangeDisplaySettings(NULL, 0);
DisableOpenGL(hWnd,hDC,hRC);
PostQuitMessage(0);
break;
default:
return DefWindowProc(hWnd, message, wParam, lParam);
}
return 0;
}
