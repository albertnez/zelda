#pragma once

#include "cTexture.h"
#include "cMap.h"
#include "utils.h"
#include <string>
#include <vector>

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
    static cRect MapLimits(int sceneX, int sceneY);
    cScene(void);
    virtual ~cScene(void);

    bool LoadLevel(int level);
    void ReloadLevel();
    void Draw(int tex_id);
    const cMap &GetMap() const;

    void SetCell(int i, int j, int value);

    void OpenDoor(int i, int j);

private:
    cMap map;  // Map of the scene.
    int id_DL;                                //actual level display list
};
