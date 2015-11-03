#pragma once

#include "cTexture.h"
#include "Globals.h"

#include <string>

enum Images : int {
    Blocks = 0,
    Player,
    Tileset,
    Sprites,
	Hearts,
    SizeImages,
};

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img, const std::string& filename,int type = GL_RGBA);

private:
	cTexture texture[Images::SizeImages];
};
