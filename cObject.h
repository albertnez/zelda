#pragma once
#include "Globals.h"
#include "utils.h"

enum ObjectType
{
    NoObject = 0,
    Sword,
    Key,
    Heart,
    Rupee,
    Star,
};

class cPlayer;


class cObject
{

    

public:
    cObject(ObjectType type, int posX, int posY, int width, int height,
            float texxo, float texyo, float texxf, float texyf);
    ~cObject();
    void Draw(int tex_id);
    bool Collides(cRect pRect);
    void DrawRect(
        int tex_id, float xo, float yo, float xf,
        float yf, int x, int y);
    virtual void Apply(cPlayer &player) = 0;
    ObjectType GetType() const;

protected:
    static const int textureWidth;
    static const int textureHeight;

private:
    int x, y, w, h;
    float xo, yo, xf, yf;
    ObjectType type;
};
