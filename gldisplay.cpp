#include "gldisplay.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "object.h"

#include <QDebug>

#define FRUSTRUM_SIZE 10.0

// current rotation angle
//static float angle = 0.f;

// array de objetos
Object modelos3d[5];

// vetor p/ guardar objetos carregados (não implementado ainda)
//std::vector<Object *> loadedModels;

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent)
{
}

void GLDisplay::initializeGL()
{
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glFrontFace(GL_CCW);

    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

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
    float light1_ambient[] = {0.2, 0.2, 0.2};
    glEnable(GL_LIGHT1);
        glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);

    // Point light (teste)
    float light3_diffuse[] = {1.0, 1.0, 1.0};
    float light3_position[] = {0.0, 1.0, 0.0, 1.0}; // x, y, z, w (w = 1 p/ ponto, 0 p/ vetor)

    //glEnable(GL_LIGHT3);
        glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
        glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
        //glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 0.9);
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(_angleX, 0.0f, 1.0f, 0.0f);
    //glRotatef(_angleY, 0.5f, 0.0f, 0.0f);

    glMatrixMode(GL_MODELVIEW);

    // === OBJETOS ===
    // não esquecer de adicionar o diretório de assets dentro do diretório de execução
    //modelos3d[0].load3dFile("assets/sala-teste.dae"); // referencia
    //modelos3d[0].render(modelos3d[0].scene, modelos3d[0].scene->mRootNode);

    modelos3d[0].load3dFile("assets/chao.dae");

    modelos3d[1].load3dFile("assets/mesa.dae");

    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.3);
    modelos3d[2].load3dFile("assets/cadeira.dae");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.73, 0.0);
    glTranslatef(-0.25, 0.0, 0.0);
    glRotatef(-45,0.0,1.0,0.0);
    // === LUZ ===
    // Spotlight (luminaria)
    float light2_diffuse[] = {1.0, 1.0, 1.0};
    float light2_ambient[] = {0.7, 0.7, 0.7};
    //float light2_position[] = {0.0, 1.2, 0.0, 1.0}; // x, y, z, w (w = 1 p/ ponto, 0 p/ vetor)
    float light2_position[] = {0.05, 0.2, 0.0, 1.0}; // x, y, z, w (w = 1 p/ ponto, 0 p/ vetor)
    //float light2_direction[] = {0.0, -1.0, 0.0}; // vetor de direção
    float light2_direction[] = {0.496139, -0.868243, 0.0}; // vetor de direção
    float light2_spot_cutoff = 50; // 0 a 180
    float light2_exponent = 5.0; // 0 a 128

    glEnable(GL_LIGHT2);
        //glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
        glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, light2_spot_cutoff);
        glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, light2_exponent);

        glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 0.8);
        //glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5);
        //glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);
    modelos3d[3].load3dFile("assets/lampada.dae");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.73, 0.1);
    modelos3d[4].load3dFile("assets/livro.dae");
    glPopMatrix();

    /* loop p/ renderizar os objetos (FIXME: não funcional, render não funciona se for chamado fora do object.cpp)
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
        gluPerspective(45, w/h, 0.5, 5);
    else
        gluPerspective(45, h/w, 0.5, 5);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

    // posicao 01 (perspectiva - visao de angulo)
//    gluLookAt(1.0,1.5,1.5,
//              -0.4,0.0,-0.4,
//              0.0,1.0,0.0);

    // posicao 02 (perspectiva - visao de angulo)
//    gluLookAt(0.8,1.5,1.1,
//              -0.14,0.175,-0.31,
//              0.0,1.0,0.0);

    // posicao 03 (topo)
//    gluLookAt(0.0,2.8,0.0,
//              0.0,0.0,0.0,
//              0.0,1.0,1.0);

    // posicao 04 (perspectiva - mesa)
    gluLookAt(-0.45,1.2,0.9,
              -0.08,0.73,0.0,
              0.0,1.0,0.0);
}

void GLDisplay::mouseMoveEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        QPoint position = event->pos();

        _angleX += (position.x() - _position.x());
        _angleY += (position.y() - _position.y());

        _position = position;

        updateGL();
    }
}

void GLDisplay::mousePressEvent(QMouseEvent *event)
{
    if( event != NULL ) {
        _position = event->pos();

    }
}
