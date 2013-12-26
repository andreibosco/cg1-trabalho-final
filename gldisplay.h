#ifndef GLDISPLAY_H
#define GLDISPLAY_H

#include <QGLWidget>

class GLDisplay : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLDisplay(QWidget *parent = 0);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    bool loadObj(const char* path);

signals:

public slots:

};

#endif // GLDISPLAY_H
