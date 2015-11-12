#include "cKey.h"


cKey::cKey() {

}

cKey::cKey(int x, int y, int w, int h):
    cObject(x, y, 0.0f, 16.0f/float(h),16.0/float(w),0.0f)
{

}


cKey::~cKey()
{
}


