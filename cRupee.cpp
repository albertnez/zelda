#include "cRupee.h"
#include "cPlayer.h"

const int cRupee::width = 8;
const int cRupee::height = 16;
const int cRupee::texxo = 22;
const int cRupee::texyo = 0;

cRupee::cRupee(int x, int y, int w, int h)
    : cObject(ObjectType::Rupee, x, y, width, height, texxo / float(w),
              (texyo + height) / float(h), (texxo + width) / float(w),
              texyo / float(h)) {}

void cRupee::Apply(cPlayer &player) {
    player.SetMoney(player.GetMoney() + 5);
}
