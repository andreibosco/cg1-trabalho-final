#ifndef OBJECT_H
#define OBJECT_H

#include <assimp/scene.h> // collects data

class Object
{
public:
    Object();

    bool load3dFile(const char* path);

    void color4_to_float4(const aiColor4D *c, float f[4]);
    void set_float4(float f[4], float a, float b, float c, float d);
    void aplicarMaterial(const aiMaterial *mtl);

    void render(const aiScene *sc, const aiNode *nd);

};

#endif // OBJECT_H
