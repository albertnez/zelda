#include "cHeart.h"
#include "cPlayer.h"

const int cHeart::width = 7;
const int cHeart::height = 8;
const int cHeart::texxo = 15;
const int cHeart::texyo = 0;

cHeart::cHeart(int x, int y, int w, int h)
    : cObject(ObjectType::Heart, x, y, width, height, texxo / float(w),
              (texyo + height) / float(h), (texxo + width) / float(w),
              texyo / float(h)) {}

void cHeart::Apply(cPlayer &player) {
    player.Heal(1);
}
