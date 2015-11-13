#include "cHeart.h"
#include "cPlayer.h"

const int cHeart::width = 7;
const int cHeart::height = 8;
const int cHeart::texxo = 15;
const int cHeart::texyo = 0;

cHeart::cHeart(int x, int y)
    : cObject(ObjectType::Heart, x, y, width, height, texxo / float(textureWidth),
              (texyo + height) / float(textureHeight),
              (texxo + width) / float(textureWidth),
              texyo / float(textureHeight)) {}

void cHeart::Apply(cPlayer &player) {
    player.Heal(1);
}
