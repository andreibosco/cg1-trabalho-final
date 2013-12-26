#include "gldisplay.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <assimp/Importer.hpp> // C++ importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // extra operations

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cassert>

#include <QDebug>

#define FRUSTRUM_SIZE 1.0

// FIXME: substituir pelo arquivo a ser lido
std::string filename = "box.obj";

// the global Assimp scene object
const struct aiScene* scene = NULL;
GLuint scene_list = 0;

// current rotation angle
static float angle = 0.f;

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

    gluLookAt(0.2,0.2,0.2,
              0.0,0.0,0.0,
              0.0,1.0,0.2);

    //renderObjects();

    std::vector<unsigned int> indices;
    std::vector<float> vertices;
    std::vector<float> uvs;
    std::vector<float> normals;

    // não esquecer de adicionar o diretório de assets dentro do diretório de execução
    loadObj("assets/cube.lxo",
            indices,
            vertices,
            uvs,
            normals);
    /*
    for (unsigned int i = 0; i < (vertices.size() / 3); i++)
    {
        int face = i;
        qDebug() << "face " << i;

        glBegin(GL_TRIANGLES);
            glColor3f(1.0, 0.0, 0.0);

            if (i == 0)
            {
                qDebug() << "vertice 1" << i;
                qDebug() << "vertice 1" << i+1;
                qDebug() << "vertice 1" << i+2;
                glVertex3f(vertices[i],
                           vertices[i+1],
                           vertices[i+2]);
            }
            else
            {
                qDebug() << "vertice 1" << i*3;
                qDebug() << "vertice 1" << i*3+1;
                qDebug() << "vertice 1" << i*3+2;
                glVertex3f(vertices[i*3],
                           vertices[i*3+1],
                           vertices[i*3+2]);
            }
        glEnd();
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

void GLDisplay::loadObj(const char* path,
                        std::vector<unsigned int> &outIndices,
                        std::vector<float> &outVertices,
                        std::vector<float> &outUVs,
                        std::vector<float> &outNormals)
{
    Assimp::Importer importer; // criando instancia de Importer
    const aiScene* scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Fast);
    aiMesh* mesh = scene->mMeshes[0]; // first mesh from file

    /*

    int numOfFaces = mesh->mNumFaces;
    int numOfIndices = numOfFaces * 3;
    outIndices.resize(numOfIndices);

    for (unsigned int i = 0; i<mesh->mNumFaces; ++i)
    {
        const aiFace &face = mesh->mFaces[i];
        assert(face.mNumIndices == 3);
        outIndices[i * 3 + 0] = face.mIndices[0];
        outIndices[i * 3 + 1] = face.mIndices[1];
        outIndices[i * 3 + 2] = face.mIndices[2];
    }

    int numOfVertices = mesh->mNumVertices;
    outVertices.resize(numOfVertices * 3);
    outNormals.resize(numOfVertices * 3);
    outUVs.resize(numOfVertices * 2);

    for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
    {
        if (mesh->HasPositions())
        {
            outVertices[i * 3 + 0] = mesh->mVertices[i].x;
            outVertices[i * 3 + 1] = mesh->mVertices[i].y;
            outVertices[i * 3 + 2] = mesh->mVertices[i].z;
        }

        if (mesh->HasNormals())
        {
            outNormals[i * 3 + 0] = mesh->mNormals[i].x;
            outNormals[i * 3 + 1] = mesh->mNormals[i].y;
            outNormals[i * 3 + 2] = mesh->mNormals[i].z;
        }

        if (mesh->HasTextureCoords(0))
        {
            outUVs[i * 2 + 0] = mesh->mTextureCoords[0][i].x;
            outUVs[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
        }
    }
    */

    for (unsigned int t = 0; t < mesh->mNumFaces; ++t)
    {
        const aiFace* face = &mesh->mFaces[t];
        GLenum face_mode;

        switch (face->mNumIndices)
        {
            case 1: face_mode = GL_POINTS; break;
            case 2: face_mode = GL_LINES; break;
            case 3: face_mode = GL_TRIANGLES; break;
            default: face_mode = GL_POLYGON; break;
        }

        glBegin(face_mode);
        glColor3f(1.0,0.0,0.0);

        for (unsigned int i = 0; i < face->mNumIndices; i++)
        {
            int index = face->mIndices[i];
            glVertex3fv(&mesh->mVertices[index].x);
        }

        glEnd();
    }
}
