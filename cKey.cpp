#include "cKey.h"
#include "cPlayer.h"

const int cKey::width = 8;
const int cKey::height = 16;
const int cKey::texxo = 0;
const int cKey::texyo = 0;

cKey::cKey(int x, int y, int w, int h)
    : cObject(ObjectType::Key, x, y, width, height, texxo / float(w),
              (texyo + height) / float(h), (texxo + width) / float(w),
              texyo / float(h)) {}

cKey::~cKey()
{
}

void cKey::Apply(cPlayer &player) {
    player.PickUp();
}
