#include "cWorm.h"
#include "cPlayer.h"
#include <cmath>

const int cWorm::width = 16;
const int cWorm::height = 16;
const float cWorm::step = 0.3;

cWorm::cWorm(int x, int y, int sceneX, int sceneY, const cPlayer &player) 
	: cBicho(x, y, width, height),
	sceneX(sceneX), sceneY(sceneY), player(player) {
	Init();
}

void cWorm::SpecificLogic(const cMap &map) {
    int tx, ty;
    player.GetPosition(&tx, &ty);
    float dx = tx - x;
    float dy = ty - y;

    float mx = dx / std::ceil(std::hypot(dx, dy)) * step;
    float my = dy / std::ceil(std::hypot(dx, dy)) * step;
    x += mx;
    if (ReachesMapLimit(map, sceneX, sceneY) || CollidesMap(map)) {
        x -= mx;
    }
    y += my;
    if (ReachesMapLimit(map, sceneX, sceneY) || CollidesMap(map)) {
        y -= my;
    }
}

void cWorm::Init() {
	animations = LoadAnimations("res/worm.anim");
	currentAnimation = "all";
    SetHitpoints(3);
    SetMaxHitpoints(3);
	w = width;
	h = height;
	stepLength = step;
	attack = 1;
    SetSpawnObjects(true);
}


