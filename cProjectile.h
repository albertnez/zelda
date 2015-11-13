#pragma once

#include "cBicho.h"

class cProjectile : public cBicho {
public:
    cProjectile(int x, int y, float sx, float sy, int sceneX, int sceneY,
                const std::string &anim, const std::string &currAnim);

    void SpecificLogic(const cMap &map) override;

private:
    float speedX;
    float speedY;
    int sceneX;
    int sceneY;
};
