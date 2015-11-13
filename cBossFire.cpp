#include "cBossFire.h"
#include <cmath>

const float cBossFire::speed = 1.337f;
const std::vector<float> cBossFire::dirToXSpeed { 0.0f, 0.0f, 0.0f, -1.0f, 1.0f };
const std::vector<float> cBossFire::dirToYSpeed { 0.0f, 1.0f, -1.0f, 0.0f, 0.0f };
const std::string cBossFire::animFilename = "res/bossFire.anim";
const std::string cBossFire::currentAnimation = "all";

cBossFire::cBossFire(int x, int y, float angle, int sceneX, int sceneY)
    : cProjectile(x, y, std::cos(angle) * speed, std::sin(angle) * speed,
                  sceneX, sceneY, animFilename, currentAnimation) {
    SetMaxHitpoints(1);
    SetHitpoints(1);
    SetAttack(2);
}
