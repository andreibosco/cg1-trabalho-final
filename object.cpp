#include "object.h"

#ifdef __APPLE__
    #include <glu.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <assimp/Importer.hpp> // C++ importer
#include <assimp/scene.h> // collects data
#include <assimp/postprocess.h> // extra operations

#include <QDebug>

Object::Object()
{
}

bool Object::load3dFile(const char* path)
{
    // criando instancia de Importer
    Assimp::Importer importer;
    scene = importer.ReadFile(path, aiProcessPreset_TargetRealtime_MaxQuality);

    if (!scene)
    {
        qDebug() << "arquivo não encontrado";
        return false;
    }

    else
    {
       render(scene, scene->mRootNode);
       return true;
    }
}

void Object::color4_to_float4(const aiColor4D *c, float f[4])
{
    f[0] = c->r;
    f[1] = c->g;
    f[2] = c->b;
    f[3] = c->a;
}

void Object::set_float4(float f[4], float a, float b, float c, float d)
{
    f[0] = a;
    f[1] = b;
    f[2] = c;
    f[3] = d;
}

void Object::aplicarMaterial(const aiMaterial *mtl)
{
    float c[4];
    int ret1, ret2;
    aiColor4D diffuse, specular, ambient, emission;
    float shininess, strength;
    unsigned int max;

    set_float4(c, 0.8f, 0.8f, 0.8f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
    {
        color4_to_float4(&diffuse, c);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

    set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
    {
        color4_to_float4(&specular, c);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);  // FIXME: desabilitado temporariamente pois a cena ficou sem contraste

    set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
    {
        color4_to_float4(&ambient, c);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

    set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
    if (AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
    {
        color4_to_float4(&emission, c);
    }
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

    max = 1;
    ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
    if (ret1 == AI_SUCCESS)
    {
        max = 1;
        ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
        if (ret2 == AI_SUCCESS)
        {
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
        }
        else
        {
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
        }
    }
    else
    {
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
        set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
    }
}

void Object::render(const aiScene *sc, const aiNode* nd)
{
    for (uint n = 0; n < nd->mNumMeshes; n++)
    {
        aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
        aplicarMaterial(sc->mMaterials[mesh->mMaterialIndex]);

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
            //glColor3f(1.0,0.0,0.0);

            for (unsigned int i = 0; i < face->mNumIndices; i++)
            {
                int index = face->mIndices[i];
                if (mesh->mNormals != NULL)
                {
                    //qDebug() << "normais ok";
                    glNormal3fv(&mesh->mNormals[index].x);
                }
                glVertex3fv(&mesh->mVertices[index].x);
            }

            glEnd();
        }

    }
    for (uint n = 0; n < nd->mNumChildren; n++)
    {
        render(sc, nd->mChildren[n]);
    }
}
