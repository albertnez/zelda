#pragma once
#include "Globals.h"
#include "utils.h"

enum ObjectType
{
    NoObject = 0,
    Sword,
    Key,
};

class cObject
{

    

public:
    
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

