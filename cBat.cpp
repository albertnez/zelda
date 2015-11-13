#include "cBat.h"
#include "cScene.h"
#include <cmath>

const int cBat::width = 16;
const int cBat::height = 8;
const int cBat::minDirectionTime = 10;
const int cBat::maxDirectionTime = 50;
const float cBat::step = 0.5;

cBat::cBat(int x, int y, int sceneX, int sceneY) 
	: cBicho(x, y, width, height),
	sceneX(sceneX), sceneY(sceneY), directionTime(0) {
	Init();
}

void cBat::SetNewDirectionTime() {
    directionTime = (rand()%(maxDirectionTime - minDirectionTime)) + minDirectionTime;
}

void cBat::SetNewDirection() {
    float a = float(rand())/RAND_MAX * (2.0f * 4.0f * std::atan(1.0f));
    sx = std::cos(a);
    sy = std::sin(a);
}

void cBat::SpecificLogic(const cMap &map) {
    if (--directionTime <= 0) {
        SetNewDirectionTime();
        SetNewDirection();
    }
    x += sx * step;
    y += sy * step;
    cRect limits = cScene::MapLimits(sceneX, sceneY);
    // Kill if it leaves the area.
    if (!limits.Intersect(GetArea())) {
        SetHitpoints(0);
    }
}

void cBat::Init() {
	animations = LoadAnimations("res/bat.anim");
	currentAnimation = "all";
    SetHitpoints(1);
    SetMaxHitpoints(1);
	w = width;
	h = height;
	stepLength = step;
	attack = 1;
    SetSpawnObjects(true);
}


