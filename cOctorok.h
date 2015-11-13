#pragma once

#include "cBicho.h"

class cOctorok : public cBicho {
public:
    cOctorok(int x, int y, int sceneX, int sceneY);

    void SpecificLogic(const cMap &map) override;
private:
    static const int width;
    static const int height;
    static const float step;
    static const std::vector<Direction> nextDir;

    void Init();
    // Which view of the scene is in.
    int sceneX;
    int sceneY;
};
