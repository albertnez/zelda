#include "cBeam.h"
#include "cScene.h"

const int cBeam::speed = 4;
cBeam::cBeam(int x, int y, int sceneX, int sceneY, Direction dir)
    : cBicho(x, y, 0, 0),
      sceneX(sceneX),
      sceneY(sceneY) {

    SetMaxHitpoints(1);
    SetHitpoints(1);
    SetAttack(1);
    SetDirection(dir);
    animations = LoadAnimations("res/beam.anim");
    currentAnimation = to_string(direction);
    w = animations[currentAnimation].CurrentFrame().width;
    h = animations[currentAnimation].CurrentFrame().height;
}

cRect cBeam::GetArea() const {
    cRect rc;
    rc.bottom = y;
    rc.top = y + animations.at(currentAnimation).CurrentFrame().height;
    rc.left = x;
    rc.right = x + animations.at(currentAnimation).CurrentFrame().width;
    return rc;
}

void cBeam::SpecificLogic(const cMap &map) {
    // Move
    float &axis = (direction == Direction::Left || direction == Direction::Right) ? x : y;
    int mult = (direction == Direction::Left || direction == Direction::Down) ? -1 : 1;
    axis += speed * mult;
    cRect limits = cScene::MapLimits(sceneX, sceneY);
    if (!limits.Intersect(GetArea())) {
        SetHitpoints(0);  // Remove, it's out of boundaries.
    }
}

