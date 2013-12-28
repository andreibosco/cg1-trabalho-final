#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>
#include <QMouseEvent>

#include "object.h"

// teste de struct p/ guardar objetos
//struct loadedModel {
//    int modelId;
//    Object * modelScene;
//};

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    void cameraPosicao(int cameraId);
    void definirIluminacao(int ilumId);

    bool light0_enable,
         light1_enable,
         light2_enable,
         light3_enable,
         light4_enable,
         light5_enable;

    int cameraInicial;

protected:
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );

private:
    float _angleX;
    float _angleY;
    QPoint _position;

signals:

public slots:

};

#endif // GLDISPLAY_H
