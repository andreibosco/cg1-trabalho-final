#include "object.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include <assimp/Importer.hpp> // C++ importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // extra operations

#include <QDebug>

Object::Object()
{
}

const aiScene* scene;

bool Object::load3dFile(const char* path)
{
    Assimp::Importer importer; // criando instancia de Importer
    scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_Fast);

    if (!scene)
    {
        qDebug() << "arquivo não encontrado";
        return false;
    }

    else
    {
       qDebug() << "arquivo carregado com sucesso";
       render(); // FIXME: render não funciona se chamado a partir do gldisplay.cpp
       return true;
    }
}

void Object::render()
{
    aiMesh* mesh = scene->mMeshes[0]; // first mesh from file

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
