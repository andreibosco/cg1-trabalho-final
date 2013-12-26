#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:
    Object();

    bool load3dFile(const char* path);
    void render();

};

#endif // OBJECT_H
