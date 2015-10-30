#pragma once

#include "cTexture.h"

// Number of tiles in the map.
#define SCENE_WIDTH	80
#define SCENE_HEIGHT	60
// The Tiles that are visible at any time.
#define VIEW_WIDTH 40
#define VIEW_HEIGHT 30

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
