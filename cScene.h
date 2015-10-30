#pragma once

#include "cTexture.h"

#define SCENE_Xo		(2*TILE_SIZE)
#define SCENE_Yo		TILE_SIZE
// Number of tiles in the map.
#define SCENE_WIDTH		72
#define SCENE_HEIGHT	28
// The Tiles that are visible at any time.
#define VIEW_WIDTH 36
#define VIEW_HEIGHT 28

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16
#define BLOCK_SIZE		24

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	int *GetMap();

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
};
