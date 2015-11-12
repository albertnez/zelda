#pragma once

#include "cBicho.h"

class cPlayer;

class cWorm : public cBicho {
public:
    cWorm(int x, int y, int sceneX, int sceneY, const cPlayer &player);

    void SpecificLogic(const cMap &map) override;
private:
    static const int width;
    static const int height;
    static const float step;

    void Init();
    // Which view of the scene is in.
    int sceneX;
    int sceneY;
    const cPlayer &player;
};
