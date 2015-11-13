#pragma once

#include "cBicho.h"

class cBat : public cBicho {
public:
    cBat(int x, int y, int sceneX, int sceneY);

    void SetNewDirectionTime();
    void SetNewDirection();
    void SpecificLogic(const cMap &map) override;
private:
    static const int width;
    static const int height;
    static const int minDirectionTime;
    static const int maxDirectionTime;
    static const float step;

    void Init();
    // Which view of the scene is in.
    int sceneX;
    int sceneY;
    int directionTime;
    float sx;
    float sy;
};
