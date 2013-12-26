#include "gldisplay.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "object.h"

#include <QDebug>

#define FRUSTRUM_SIZE 10.0

// the global Assimp scene object
//const struct aiScene* scene = NULL;
//GLuint scene_list = 0;

// current rotation angle
//static float angle = 0.f;

Object modelos3d[2];

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent)
{
}

void GLDisplay::initializeGL()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glColor3f(1.0,1.0,1.0);

    // Lightning
    glEnable(GL_LIGHTING);

    // Shade Model
    glShadeModel(GL_SMOOTH); // GL_FLAT or GL_SMOOTH

    // Diffuse light
    float light0_diffuse[] = {0.5, 0.5, 0.5};
    float light0_specular[] = {1.0, 1.0, 1.0};

    glEnable(GL_LIGHT0);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);

    // Ambient light
    float light2_ambient[] = {0.2, 0.2, 0.2};
    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light2_ambient);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);

//    gluLookAt(1.0,0.0,0.0,
//              0.0,0.0,0.0,
//              0.0,1.0,0.0);

    // não esquecer de adicionar o diretório de assets dentro do diretório de execução
    modelos3d[0].load3dFile("assets/sala-teste.dae");
    modelos3d[1].load3dFile("assets/cube-yellow.dae");

    //modelos3d[0].render();

    /*
    for (int i = 0; i < 2; i++)
    {
        modelos3d[i].render();
    }
    */

    glFlush();

}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glLoadIdentity();

    if ( w>= h )
        gluPerspective(45, w/h, 1, 5);
    else
        gluPerspective(45, h/w, 1, 5);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    // posicao 01
//    gluLookAt(1.0,1.5,1.5,
//              -0.4,0.0,-0.4,
//              0.0,1.0,0.0);

    // posicao 02
    gluLookAt(0.8,1.5,1.1,
              -0.14,0.175,-0.31,
              0.0,1.0,0.0);
}
