#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>

#include "object.h"

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    bool light0_enable,
         light1_enable,
         light2_enable,
         light3_enable,
         light4_enable,
         light5_enable;

    QString texto;

    int cameraInicial;

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    void renderizarObjetos();
    void rotacaoHora(int elementoHora);
    void textoNotebook(QString texto);
    void definirIluminacao(int ilumId);
    void cameraPosicao(int cameraId);
    void cameraCustom(float px, float py, float pz,
                      float tx, float ty, float tz,
                      float ux, float uy, float uz);
    float modulo(float x, float y, float z);

private:
    float _angleX;
    float _angleY;
    QPoint _position;

signals:

public slots:

};

#endif // GLDISPLAY_H
