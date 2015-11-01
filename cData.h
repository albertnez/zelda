#pragma once

#include "cTexture.h"
#include "Globals.h"

#include <string>

//Image array size
#define NUM_IMG		3

//Image identifiers
#define IMG_BLOCKS	0
#define IMG_PLAYER	1
extern const int IMG_TILESET;
/*
#define IMG_ENEMY1	2
#define IMG_ENEMY2	3
#define IMG_SHOOT	4
...
*/

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img, const std::string& filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
