#pragma once

#include "cProjectile.h"

class cBossFire : public cProjectile {
public:
    cBossFire(int x, int y, float angle, int sceneX, int sceneY);
    
private:
    static const float speed;
    static const std::vector<float> dirToXSpeed;
    static const std::vector<float> dirToYSpeed;
    static const std::string animFilename;
    static const std::string currentAnimation;
};
