#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>

#include "object.h"

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    void renderizarObjetos();
    void cameraPosicao(int cameraId);
    void definirIluminacao(int ilumId);
    void rotacaoHora(int elementoHora);
    void textoNotebook(QString texto);

    bool light0_enable,
         light1_enable,
         light2_enable,
         light3_enable,
         light4_enable,
         light5_enable;

    int cameraInicial;

    QString texto;

private:
    float _angleX;
    float _angleY;
    QPoint _position;

signals:

public slots:

};

#endif // GLDISPLAY_H
