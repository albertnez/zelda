#pragma once

#include "cBicho.h"
#include <list>
#include <memory>

class cBoss : public cBicho {
public:
    cBoss(int x, int y, int sceneX, int sceneY, std::list<std::unique_ptr<cBicho>> &enemies);

    void SpecificLogic(const cMap &map) override;
private:
    void Init();
    void SetNewFireTime();
    void SetNewDirectionTime();
    void SetNewDirection();
    void Fire();
    void FireSingle(float angle);

    static const int width;
    static const int height;
    static const int minDirectionTime;
    static const int maxDirectionTime;
    static const int minFireTime;
    static const int maxFireTime;
    static const float step;
    static const float shootAngle;

    // Which view of the scene is in.
    int sceneX;
    int sceneY;
    int directionTime;
    int fireTime;

    std::list<std::unique_ptr<cBicho>> &enemies;
};
