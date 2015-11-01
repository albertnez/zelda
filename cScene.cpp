#include "cScene.h"
#include "Globals.h"
#include <iostream>
#include <fstream>

const int VIEW_WIDTH = 16;
const int VIEW_HEIGHT = 11;

const std::string FILENAME = "level";
const std::string FILENAME_EXT = ".txt";

const int TILE_SIZE = 16;
const int BLOCK_SIZE = 24;

const int TILESET_WIDTH = 18;
const int TILESET_HEIGHT = 8;


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
		std::cerr << "Error loading " << file << std::endl;
		return false;
	}

	int sceneWidth, sceneHeight;
	ifs >> sceneWidth >> sceneHeight;
	map = Map(sceneHeight, std::vector<int>(sceneWidth, 0));

	std::cerr << "width: " << sceneWidth << " height: " << sceneHeight << std::endl;
	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);

	glBegin(GL_QUADS);

	for (j = sceneHeight - 1; j >= 0; j--) {
		px=0;
		py=(j*TILE_SIZE);

		for (i=0; i< sceneWidth; i++) {
			ifs >> map[j][i];

			coordx_tile = double(map[j][i] % TILESET_WIDTH) / (TILESET_WIDTH);
			coordy_tile = double(map[j][i] / TILESET_WIDTH) / (TILESET_HEIGHT);

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

void cScene::Draw(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}
const cScene::Map& cScene::GetMap() const
{
	return map;
}
