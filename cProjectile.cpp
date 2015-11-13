#include "cProjectile.h"
#include "cScene.h"

cProjectile::cProjectile(int x, int y, float sx, float sy, int sceneX,
                         int sceneY, const std::string &anim, const std::string &currAnim)
    : cBicho(x, y, 0, 0),
      speedX(sx),
      speedY(sy),
      sceneX(sceneX),
      sceneY(sceneY) {

    animations = LoadAnimations(anim);
    SetAnimation(currAnim);
    SetWidthHeight(animations[currAnim].CurrentFrame().width,
                   animations[currAnim].CurrentFrame().height);
    EnableDyingAnimation(false);
}

void cProjectile::SpecificLogic(const cMap &map) {
    x += speedX;
    y += speedY;
    cRect limits = cScene::MapLimits(sceneX, sceneY);
    if (!limits.Intersect(GetArea())) {
        SetHitpoints(0);  // Remove, it's out of boundaries.
    }
}
