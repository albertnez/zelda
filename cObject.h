#pragma once
#include "Globals.h"
#include "utils.h"
class cObject
{

    

public:
    enum Type
    {
        key = 0,
    };
    cObject();
    cObject(
        int posX, int posY, float texxo,
        float texyo, float texxf, float texyf);
    ~cObject();
    void Draw(int tex_id);
    bool Collides(cRect pRect);
    void DrawRect(
        int tex_id, float xo, float yo, float xf,
        float yf, int x, int y, int w, int h);

private:
    int x, y;
    float xo, yo, xf, yf;
};

