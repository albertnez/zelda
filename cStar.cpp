#include "cStar.h"
#include "cPlayer.h"

const int cStar::width = 16;
const int cStar::height = 16;
const int cStar::texxo = 30;
const int cStar::texyo = 0;

cStar::cStar(int x, int y)
    : cObject(ObjectType::Star, x, y, width, height, texxo / float(textureWidth),
              (texyo + height) / float(textureHeight),
              (texxo + width) / float(textureWidth),
              texyo / float(textureHeight)) {}

void cStar::Apply(cPlayer &player) {
    player.PickStar();
}
