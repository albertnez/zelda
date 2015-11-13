#pragma once

#include "cObject.h"

class cPlayer;

class cHeart :
    public cObject
{
public:
    cHeart(int x, int y, int w, int h);

    void Apply(cPlayer &player) override;

private:
    static const int width;
    static const int height;
    static const int texxo;
    static const int texyo;
};

