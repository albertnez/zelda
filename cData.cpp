#include "cData.h"

const int IMG_TILESET = 2;

cData::cData(void) {}
cData::~cData(void){}

int cData::GetID(int img)
{
	return texture[img].GetID();
}

void cData::GetSize(int img, int *w, int *h)
{
	texture[img].GetSize(w,h);
}

bool cData::LoadImage(int img, const std::string& filename, int type)
{
	int res;

	res = texture[img].Load(filename.c_str(),type);
	if(!res) return false;

	return true;
}
