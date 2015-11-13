#pragma once

#include "cProjectile.h"

class cBeam : public cProjectile {
public:
    cBeam(int x, int y, int sceneX, int sceneY, Direction dir);
    
private:
    static const int speed;
    static const std::vector<float> dirToXSpeed;
    static const std::vector<float> dirToYSpeed;
    static const std::string animFilename;
};
