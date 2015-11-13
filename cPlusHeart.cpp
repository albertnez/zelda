#include "cPlusHeart.h"
#include "cPlayer.h"

const int cPlusHeart::width = 13;
const int cPlusHeart::height = 13;
const int cPlusHeart::texxo = 45;
const int cPlusHeart::texyo = 0;

cPlusHeart::cPlusHeart(int x, int y)
    : cObject(ObjectType::PlusHeart, x, y, width, height, texxo / float(textureWidth),
              (texyo + height) / float(textureHeight),
              (texxo + width) / float(textureWidth),
              texyo / float(textureHeight)) {}

void cPlusHeart::Apply(cPlayer &player) {
    player.SetMaxHitpoints(player.GetMaxHitpoints() + 2);
    player.Heal(2);
}
