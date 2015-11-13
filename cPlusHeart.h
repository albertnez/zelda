#pragma once

#include "cObject.h"

class cPlayer;

class cPlusHeart :
    public cObject
{
public:
    cPlusHeart(int x, int y);

    void Apply(cPlayer &player) override;

private:
    static const int width;
    static const int height;
    static const int texxo;
    static const int texyo;
};

