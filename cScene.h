#pragma once

#include "cTexture.h"
#include <string>
#include <vector>

// Number of tiles in the map.
extern const int SCENE_WIDTH;
extern const int SCENE_HEIGHT;
// The Tiles that are visible at any time.
extern const int VIEW_WIDTH;
extern const int VIEW_HEIGHT;

extern const std::string FILENAME;
extern const std::string FILENAME_EXT;

extern const int TILE_SIZE;
extern const int BLOCK_SIZE;

// Number of tiles in the tileset image.
extern const int TILESET_WIDTH;
extern const int TILESET_HEIGHT;


class cScene
{
public:
	typedef std::vector<std::vector<int>> Map;
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	const Map& GetMap() const;

private:
	Map map;  // Map of the scene.
	int id_DL;								//actual level display list
};
