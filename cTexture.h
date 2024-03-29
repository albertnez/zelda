#pragma once

#include "Globals.h"

#include <string>

class cTexture
{
public:
    cTexture(void);
    ~cTexture(void);

    bool Load(const std::string& filename,int type = GL_RGBA,int wraps = GL_REPEAT,int wrapt = GL_REPEAT,
              int magf = GL_NEAREST,int minf = GL_NEAREST,bool mipmap = false);
    int  GetID();
    void GetSize(int *w,int *h);

private:
    GLuint id;
    int width;
    int height;
};
