#pragma once

#include "cObject.h"

class cPlayer;

class cStar :
    public cObject
{
public:
    cStar(int x, int y);

    void Apply(cPlayer &player) override;

private:
    static const int width;
    static const int height;
    static const int texxo;
    static const int texyo;
};

