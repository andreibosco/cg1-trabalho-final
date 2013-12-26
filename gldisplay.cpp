#include "gldisplay.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "object.h"

#include <QDebug>

#define FRUSTRUM_SIZE 1.0

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

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glColor3f(1.0,1.0,1.0);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);

    gluLookAt(0.0,0.0,1.0,
              0.0,0.0,0.0,
              0.0,1.0,0.2);

    // não esquecer de adicionar o diretório de assets dentro do diretório de execução
    modelos3d[0].load3dFile("assets/sala-teste.lxo");
    modelos3d[1].load3dFile("assets/cube.lxo");

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

    if ( w>= h )
        glOrtho(-FRUSTRUM_SIZE * w / h,
                 FRUSTRUM_SIZE * w / h,
                -FRUSTRUM_SIZE,
                 FRUSTRUM_SIZE,
                -FRUSTRUM_SIZE,
                 FRUSTRUM_SIZE);
    else
        glOrtho(-FRUSTRUM_SIZE,
                 FRUSTRUM_SIZE,
                -FRUSTRUM_SIZE * h / w,
                 FRUSTRUM_SIZE * h / w,
                -FRUSTRUM_SIZE,
                 FRUSTRUM_SIZE);
}
