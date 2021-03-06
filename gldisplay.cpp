#include "gldisplay.h"
#include "object.h"

#ifdef __APPLE__
    #include <glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <QDateTime>

// array de path dos arquivos
char* arquivos[] = {(char *)"assets/chao.dae",
                    (char *)"assets/mesa.dae",
                    (char *)"assets/cadeira.dae",
                    (char *)"assets/lampada.dae",
                    (char *)"assets/livro.dae",
                    (char *)"assets/violao.dae",
                    (char *)"assets/parede_janela.dae",
                    (char *)"assets/parede.dae",
                    (char *)"assets/prateleira.dae",
                    (char *)"assets/prateleira.dae",
                    (char *)"assets/lava_lamp_vidro.dae",
                    (char *)"assets/notebook.dae",
                    (char *)"assets/relogio.dae",
                    (char *)"assets/ponteiro_hora.dae",
                    (char *)"assets/ponteiro_minuto.dae"};
int const arquivosSize = (sizeof(arquivos)/sizeof(*arquivos));

// array de objetos
Object modelos3d[arquivosSize];

// camera inicial
int cameraInicial;

// Luzes
bool light4_enable;

GLDisplay::GLDisplay(QWidget *parent) :
    QGLWidget(parent)
{
}

void GLDisplay::initializeGL()
{
    /**
      * Definicões gerais do openGL
      */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    // Cor de background e cor padrão
    glClearColor(0.9f, 0.9f, 1.0f, 1.0f); // dia
    //glClearColor(0.05f, 0.05f, 0.05f, 1.0f); // noite
    glColor3f(1.0,1.0,1.0);

    // Iluminação
    glEnable(GL_LIGHTING);
    glShadeModel(GL_SMOOTH); // Shade Model: GL_FLAT ou GL_SMOOTH

    // Blend (necessário p/ transparência por alpha)
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    /**
      * Definições das luzes
      */
    // GL_LIGHT0: Luz de preenchimento
    float light0_diffuse[] = {0.5, 0.5, 0.5};
    float light0_specular[] = {1.0, 1.0, 1.0};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glEnable(GL_LIGHT0);

    // GL_LIGHT1: Luz ambiente
    float light1_ambient[] = {0.4, 0.4, 0.4};
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glEnable(GL_LIGHT1);

    // GL_LIGHT2: Luminária de mesa
    // Luz em MODELVIEW p/ ser afetada pela posição da câmera
    light2_enable = false;

    // GL_LIGHT3: Luz direcional (sol)
    // Luz em MODELVIEW p/ ser afetada pela posição da câmera
    light3_enable = true;

    // GL_LIGHT4: Lava lamp
    // Luz em MODELVIEW p/ ser afetada pela posição da câmera
    light4_enable = false;

    // GL_LIGHT5: Tela notebook
    // Luz em MODELVIEW p/ ser afetada pela posição da câmera
    light5_enable = false;

    // Definindo status da camera inicial
    cameraInicial = 1;

    // Texto inicial do notebook
    texto = "CG 2013.2";
}

void GLDisplay::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderizarObjetos();
}

void GLDisplay::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);

    glViewport(0, 0, w, h);

    glLoadIdentity();

    if ( w>= h )
        gluPerspective(40, w/h, 0.5, 5);
    else
        gluPerspective(40, h/w, 0.5, 5);

    if (cameraInicial == 1)
    {

        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        cameraCustom(1.6, 1.7, 2.2,
                    -0.5, 0.6, 0.0,
                     1.6, 2.0, 2.2);
    }

    glMatrixMode(GL_MODELVIEW);
}

void GLDisplay::renderizarObjetos()
{
    /**
      * Objetos 3D do cenário
      *
      * (não esquecer de adicionar o diretório de assets dentro do diretório de execução)
      *
      */

    // GL_LIGHT3: Luz direcional (sol)
    float light3_diffuse[] = {1.0, 1.0, 1.0};
    float light3_position[] = {0.0, 0.707107, -0.707107, 0.0}; // x, y, z, w (w = 1 p/ ponto, 0 p/ vetor)
    glLightfv(GL_LIGHT3, GL_DIFFUSE, light3_diffuse);
    glLightfv(GL_LIGHT3, GL_POSITION, light3_position);
    if (light3_enable)
        glEnable(GL_LIGHT3);
    else
        glDisable(GL_LIGHT3);

    // loop de renderização dos objetos
    for (int i = 0; i<arquivosSize; i++)
    {
        glPushMatrix();

        if (i == 0) // chao
        {
            glTranslatef(0.0, 0.0, 1.0);
        }
        if (i == 2) // cadeira
        {
            glTranslatef(0.0, 0.0, 0.3);
        }
        if (i == 3) // luminária
        {
            glTranslatef(-0.25, 0.73, 0.0);
            glRotatef(-45,0.0,1.0,0.0);
            // GL_LIGHT2: Luz luminária de mesa
            float light2_diffuse[] = {1.0, 1.0, 1.0};
            float light2_position[] = {0.05, 0.2, 0.0, 1.0}; // x, y, z, w (w = 1 p/ ponto, 0 p/ vetor)
            float light2_direction[] = {0.496139, -0.868243, 0.0}; // vetor de direção (normalizado)
            float light2_spot_cutoff = 50; // 0 a 180
            float light2_exponent = 5.0; // 0 a 128
            glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
            glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
            glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_direction);
            glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, light2_spot_cutoff);
            glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, light2_exponent);
            glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.2);
            if (light2_enable)
                glEnable(GL_LIGHT2);
            else
                glDisable(GL_LIGHT2);
        }
        if (i == 4) // livro
        {
            glTranslatef(-0.06, 0.73, 0.15);
        }
        if (i == 5) // violao
        {
            glTranslatef(0.625, 0.0, 0.0);
            glRotatef(90, 0.0, 1.0, 0.0);
            glRotatef(-10, 1.0, 0.0, 0.0);
        }
        if (i == 6) // parede com janela
        {
            glTranslatef(0.0, 0.0, -0.45);
        }
        if (i == 7) // parede
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            glTranslatef(-1.15, 0.0, -1.2);
        }
        if (i == 8) // prateleira 1
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            glTranslatef(-0.5, 0.9, -1.0);
        }
        if (i == 9) // prateleira 2
        {
            glRotatef(90, 0.0, 1.0, 0.0);
            glTranslatef(-0.5, 1.5, -1.0);
        }
        if (i == 10) // lava lamp
        {
            glTranslatef(-1.0, 0.93, 0.5);
            float light4_diffuse[] = {0.5, 0.0, 0.0};
            float light4_specular[] = {1.0, 1.0, 1.0};
            float light4_position[] = {0.0, 0.3, 0.0, 1.0};
            glLightfv(GL_LIGHT4, GL_DIFFUSE, light4_diffuse);
            glLightfv(GL_LIGHT4, GL_SPECULAR, light4_specular);
            glLightfv(GL_LIGHT4, GL_POSITION, light4_position);
            glLightf(GL_LIGHT4, GL_QUADRATIC_ATTENUATION, 0.2);
            if (light4_enable == true)
                glEnable(GL_LIGHT4);
            else
                glDisable(GL_LIGHT4);
        }
        if (i == 11) // notebook
        {

            glRotatef(160, 0.0, 1.0, 0.0);
            glTranslatef(-0.20, 0.73, 0.2);
            float light5_diffuse[] = {0.0, 0.0, 0.5};
            float light5_position[] = {0.0, 0.1, 0.0, 1.0};
            glLightfv(GL_LIGHT5, GL_DIFFUSE, light5_diffuse);
            glLightfv(GL_LIGHT5, GL_POSITION, light5_position);
            glLightf(GL_LIGHT5, GL_QUADRATIC_ATTENUATION, 0.2);
            if (light5_enable == true)
                glEnable(GL_LIGHT5);
            else
                glDisable(GL_LIGHT5);
            textoNotebook(texto); // texto exibido na tela do notebook
        }
        if (i == 12 || i == 13 || i == 14) // relogio e ponteiros
        {
            glTranslatef(-1.0, 0.93, 0.15);
            glRotatef(70, 0.0, 1.0, 0.0);
        }
        if (i == 13 ) // ponteiro de hora
        {
            rotacaoHora(0);
        }
        if (i == 14) // ponteiro do minuto
        {
            rotacaoHora(1);
        }

        modelos3d[i].load3dFile(arquivos[i]);

        glPopMatrix();
    }

    glFlush();
}

void GLDisplay::rotacaoHora(int elementoHora)
{
    // Ids:
    // 0 = hora;
    // 1 = minuto;

    // criando objeto da hora
    QTime horaCompleta = QTime::currentTime();
    float hora = horaCompleta.hour();
    float minuto = horaCompleta.minute();
    float angulo;

    // posicionando no eixo e aplicando rotação
    // de acordo com o elemento e com a hora atual
    glTranslatef(0.0, 0.16, 0.0);

    if (elementoHora == 0)
    {
        angulo = hora * 30;
    }
    else
    {
        angulo = minuto * 6;
    }
    glRotatef(-angulo, 0.0, 0.0, 1.0);

    glTranslatef(0.0, -0.16, 0.0);

}

void GLDisplay::textoNotebook(QString texto)
{
    glPushMatrix();

    glDisable(GL_LIGHTING);

    glColor3f(1.0, 1.0, 1.0);

    glScalef(0.45, 0.45, 0.45);
    glTranslatef(0.3, 0.3, 0.22);
    glRotatef(10, 1.0, 0.0, 0.0);
    glRotatef(180, 0.0, 1.0, 0.0);

    QPainterPath path;
    QFont font("Arial");
    font.setPixelSize(1);
    path.addText(QPointF(0, 0), font, QString(texto));
    QList<QPolygonF> poly = path.toSubpathPolygons();
    for (QList<QPolygonF>::iterator i = poly.begin(); i != poly.end(); i++){
        glBegin(GL_LINE_LOOP);
        for (QPolygonF::iterator p = (*i).begin(); p != i->end(); p++)
            glVertex3f(p->rx()*0.1f, -p->ry()*0.1f, 0);
        glEnd();
    }

    glEnable(GL_LIGHTING);

    glPopMatrix();
}

void GLDisplay::definirIluminacao(int ilumId)
{
    // Ids:
    // 0 = dia
    // 1 = noite
    if (ilumId == 0)
    {
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHT1);
        glClearColor(0.9f, 0.9f, 1.0f, 1.0f);
        light2_enable = false;
        light3_enable = true;
        light4_enable = false;
        light5_enable = false;
    }
    else
    {
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHT1);
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        light2_enable = true;
        light3_enable = false;
        light4_enable = true;
        light5_enable = true;
    }

    updateGL();
}

void GLDisplay::cameraPosicao(int cameraId)
{
    cameraInicial = 0;
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (cameraId == 0)
    {
        cameraCustom(1.6, 1.7, 2.2,
                    -0.5, 0.6, -0.01,
                     1.6, 2.0, 2.2);
    }
    else if (cameraId == 1)
    {
        cameraCustom(0.8, 1.5, 1.1,
                    -0.14, 0.175,-0.31,
                     0.8, 2.5, 1.1);
    }
    else if (cameraId == 2)
    {
        cameraCustom(-0.45, 1.2, 0.9,
                      0.0, 0.73, 0.0,
                     -0.45, 2.0, 0.9);
    }
    else if (cameraId == 3)
    {
        cameraCustom(0.0, 2.8, 0.0,
                     0.0, 0.0, 0.0,
                     0.0, 1.0, 1.0);
    }

    updateGL();
}

void GLDisplay::cameraCustom(float px, float py, float pz, // eye
                             float tx, float ty, float tz, // target
                             float ux, float uy, float uz) // up vector
{
    // matriz mundo p/ camera
    float K[3] = {px - tx, py - ty, pz - tz};
    float modK = modulo(K[0],K[1],K[2]);
    float k[3] = {K[0]/modK, K[1]/modK, K[2]/modK};

    float Ia[3] = {ux - px, uy - py, uz - pz};
    float I[3] = { Ia[1] * K[2] - Ia[2] * K[1],
                   Ia[2] * K[0] - Ia[0] * K[2],
                   Ia[0] * K[1] - Ia[1] * K[0]};
    float modI = modulo(I[0],I[1],I[2]);
    float i[3] = {I[0]/modI, I[1]/modI, I[2]/modI};

    float j[3] = { k[1] * i[2] - k[2] * i[1],
                   k[2] * i[0] - k[0] * i[2],
                   k[0] * i[1] - k[1] * i[0]};

    float M[16] = {i[0], j[0], k[0], 0,
                   i[1], j[1], k[1], 0,
                   i[2], j[2], k[2], 0,
                   -(i[0]*px+i[1]*py+i[2]*pz), -(j[0]*px+j[1]*py+j[2]*pz), -(k[0]*px+k[1]*py+k[2]*pz), 1.0};

    // carregando a matrix M (mundo p/ camera)
    glLoadMatrixf(M);

    updateGL();
}

float GLDisplay::modulo(float x, float y, float z)
{
    return sqrt(x*x + y*y + z*z);
}
