#pragma once

#include "cObject.h"

class cPlayer;

class cRupee :
    public cObject
{
public:
    cRupee(int x, int y, int w, int h);

    void Apply(cPlayer &player) override;

private:
    static const int width;
    static const int height;
    static const int texxo;
    static const int texyo;
};

