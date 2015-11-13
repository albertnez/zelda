#include "cKey.h"
#include "cPlayer.h"

const int cKey::width = 8;
const int cKey::height = 16;
const int cKey::texxo = 0;
const int cKey::texyo = 0;

cKey::cKey(int x, int y)
    : cObject(ObjectType::Key, x, y, width, height, texxo / float(textureWidth),
              (texyo + height) / float(textureHeight),
              (texxo + width) / float(textureWidth),
              texyo / float(textureHeight)) {}

cKey::~cKey()
{
}

void cKey::Apply(cPlayer &player) {
    player.PickUp();
}
