#include "cScene.h"
#include "Globals.h"
#include <fstream>

const int VIEW_WIDTH = 16;
const int VIEW_HEIGHT = 11;

const std::string FILENAME = "level";
const std::string FILENAME_EXT = ".txt";

const int TILE_SIZE = 16;
const int BLOCK_SIZE = 24;

const int TILESET_WIDTH = 32;
const int TILESET_HEIGHT = 32;

cRect cScene::MapLimits(int sceneX, int sceneY) {
    return {
        VIEW_WIDTH * TILE_SIZE * sceneX,     // left
        VIEW_HEIGHT * TILE_SIZE * -~sceneY,  // top
        VIEW_WIDTH * TILE_SIZE * -~sceneX,   // right
        VIEW_HEIGHT * TILE_SIZE * sceneY,    // bottom
    };
}

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

bool cScene::LoadLevel(int level)
{
    bool res;
    int i,j,px,py;
    float coordx_tile, coordy_tile;

    res=true;

    std::string file{FILENAME + (level < 10 ? "0" : "") + std::to_string(level) + FILENAME_EXT};

    std::ifstream ifs(file);
    if (!ifs.good()) {
        throw std::runtime_error("Error loading " + file);
    }

    int sceneWidth, sceneHeight;
    ifs >> sceneWidth >> sceneHeight;

    map = cMap(sceneWidth, sceneHeight);

    id_DL=glGenLists(1);
    glNewList(id_DL,GL_COMPILE);

    glBegin(GL_QUADS);

    for (j = sceneHeight - 1; j >= 0; j--) {
        px=0;
        py=(j*TILE_SIZE);

        for (i=0; i< sceneWidth; i++) {
            int tile;
            ifs >> tile;
            --tile;
            map.SetCell(i, j, tile+1);

            coordx_tile = double(tile % TILESET_WIDTH) / (TILESET_WIDTH);
            coordy_tile = double(tile / TILESET_WIDTH) / (TILESET_HEIGHT);

            const double tilesetXPixels = 1./TILESET_WIDTH;
            const double tilesetYPixels = 1./TILESET_HEIGHT;

            glTexCoord2f(coordx_tile, coordy_tile + tilesetYPixels); 
            glVertex2i(px, py);

            glTexCoord2f(coordx_tile + tilesetXPixels, coordy_tile + tilesetYPixels); 
            glVertex2i(px + TILE_SIZE, py);

            glTexCoord2f(coordx_tile + tilesetXPixels, coordy_tile);
            glVertex2i(px + TILE_SIZE, py + TILE_SIZE);

            glTexCoord2f(coordx_tile, coordy_tile);
            glVertex2i(px, py + TILE_SIZE);

            px+=TILE_SIZE;
        }
    }

    glEnd();
    glEndList();

    ifs.close();

    return res;
}


void cScene::ReloadLevel()
{
    bool res;
    int i, j, px, py;
    float coordx_tile, coordy_tile;

    int sceneWidth, sceneHeight;
    sceneWidth = map.Width();
    sceneHeight = map.Height();

    id_DL = glGenLists(1);
    glNewList(id_DL, GL_COMPILE);

    glBegin(GL_QUADS);

    for (j = sceneHeight - 1; j >= 0; j--) {
        px = 0;
        py = (j*TILE_SIZE);

        for (i = 0; i< sceneWidth; i++) {
            int tile = map.GetCell(j,i);
            --tile;

            coordx_tile = double(tile % TILESET_WIDTH) / (TILESET_WIDTH);
            coordy_tile = double(tile / TILESET_WIDTH) / (TILESET_HEIGHT);

            const double tilesetXPixels = 1. / TILESET_WIDTH;
            const double tilesetYPixels = 1. / TILESET_HEIGHT;

            glTexCoord2f(coordx_tile, coordy_tile + tilesetYPixels);
            glVertex2i(px, py);

            glTexCoord2f(coordx_tile + tilesetXPixels, coordy_tile + tilesetYPixels);
            glVertex2i(px + TILE_SIZE, py);

            glTexCoord2f(coordx_tile + tilesetXPixels, coordy_tile);
            glVertex2i(px + TILE_SIZE, py + TILE_SIZE);

            glTexCoord2f(coordx_tile, coordy_tile);
            glVertex2i(px, py + TILE_SIZE);

            px += TILE_SIZE;
        }
    }

    glEnd();
    glEndList();
}

void cScene::Draw(int tex_id)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,tex_id);
    glCallList(id_DL);
    glDisable(GL_TEXTURE_2D);
}
const cMap &cScene::GetMap() const
{
    return map;
}

void cScene::SetCell(int i, int j, int value) {
    map.SetCell(i, j, value);
    ReloadLevel();
}

void cScene::OpenDoor(int i, int j) {
    map.OpenDoor(i, j);
    ReloadLevel();
}