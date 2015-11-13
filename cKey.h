#pragma once
#include "cObject.h"
class cKey :
    public cObject
{
public:
    cKey(int x, int y);
    ~cKey();

    void Apply(cPlayer &player) override;

private:
    static const int width;
    static const int height;
    static const int texxo;
    static const int texyo;
};

