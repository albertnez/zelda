#include "cBeam.h"

const int cBeam::speed = 4;
const std::vector<float> cBeam::dirToXSpeed { 0.0f, 0.0f, 0.0f, -1.0f, 1.0f };
const std::vector<float> cBeam::dirToYSpeed { 0.0f, 1.0f, -1.0f, 0.0f, 0.0f };
const std::string cBeam::animFilename = "res/beam.anim";

cBeam::cBeam(int x, int y, int sceneX, int sceneY, Direction dir)
    : cProjectile(x, y, dirToXSpeed[dir] * speed, dirToYSpeed[dir] * speed,
                  sceneX, sceneY, animFilename, to_string(dir)) {
    SetMaxHitpoints(1);
    SetHitpoints(1);
    SetAttack(1);
    SetDirection(dir);
}
