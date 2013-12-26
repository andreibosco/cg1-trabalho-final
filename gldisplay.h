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

    void loadObj(const char* path,
                 std::vector<unsigned int> &outIndices,
                 std::vector<float> &outVertices,
                 std::vector<float> &outUVs,
                 std::vector<float> &outNormals);

signals:

public slots:

};

#endif // GLDISPLAY_H
