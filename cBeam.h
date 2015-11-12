#pragma once

#include "cBicho.h"

class cBeam : public cBicho {
public:
    cBeam(int x, int y, int sceneX, int sceneY, Direction dir);

    
    cRect GetArea() const override;
    void SpecificLogic(const cMap &map) override;
private:
    static const int speed;
    static const std::vector<Direction> nextDir;

    // Which view of the scene is in.
    int sceneX;
    int sceneY;
};
