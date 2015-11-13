#include "cBoss.h"
#include "cScene.h"
#include "cBossFire.h"
#include <cmath>

const int cBoss::width = 24;
const int cBoss::height = 32;
const int cBoss::minDirectionTime = 5;
const int cBoss::maxDirectionTime = 15;
const int cBoss::minFireTime = 80;
const int cBoss::maxFireTime = 160;
const float cBoss::step = 0.2;
const float cBoss::shootAngle = 4.0f * std::atan(1.0f) / 8.0f;

cBoss::cBoss(int x, int y, int sceneX, int sceneY, std::list<std::unique_ptr<cBicho>> &enemies) 
	: cBicho(x, y, width, height),
	sceneX(sceneX), sceneY(sceneY), directionTime(0), fireTime(0), enemies(enemies) {
	Init();
}

void cBoss::SpecificLogic(const cMap &map) {
    if (--fireTime <= 0) {
        SetNewFireTime();
        Fire();
    }
    if (--directionTime <= 0) {
        SetNewDirectionTime();
        SetNewDirection();
    }
    Move(map, direction, sceneX, sceneY);
}

void cBoss::Init() {
	animations = LoadAnimations("res/boss.anim");
	currentAnimation = "all";
    SetHitpoints(5);
    SetMaxHitpoints(5);
	w = width;
	h = height;
	stepLength = step;
	attack = 2;
}

void cBoss::SetNewFireTime() {
    fireTime = (rand()%(maxFireTime - minFireTime)) + minFireTime;
}

void cBoss::SetNewDirectionTime() {
    directionTime = (rand()%(maxDirectionTime - minDirectionTime)) + minDirectionTime;
}

void cBoss::SetNewDirection() {
    switch (rand()%4) {
        case 0:
            SetDirection(Direction::Up);
            break;
        case 1:
            SetDirection(Direction::Down);
            break;
        case 2:
            SetDirection(Direction::Left);
            break;
        case 3:
        default:
            SetDirection(Direction::Right);
            break;
    }
}

void cBoss::Fire() {
    FireSingle(shootAngle);
    FireSingle(0.0f);
    FireSingle(8.0f * atan(1.0f) - shootAngle);
}

void cBoss::FireSingle(float angle) {
    int nx = x + w/2;
    int ny = y + h/2;
    enemies.push_back(
        std::unique_ptr<cBicho>(new cBossFire(nx, ny, angle, sceneX, sceneY)));
}
