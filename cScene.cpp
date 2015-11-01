#include "cScene.h"
#include "Globals.h"
#include <iostream>
#include <fstream>

const int SCENE_WIDTH = 80;
const int SCENE_HEIGHT = 60;

const int VIEW_WIDTH = 40;
const int VIEW_HEIGHT = 30;

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
	map = Map(SCENE_HEIGHT, std::vector<int>(SCENE_WIDTH, 0));
	bool res;
	int i,j,px,py;
	char tile;
	float coordx_tile, coordy_tile;

	res=true;

	std::string file{FILENAME + (level < 10 ? "0" : "") + std::to_string(level) + FILENAME_EXT};

	std::ifstream ifs(file);
	if (!ifs.good()) {
		std::cerr << "Error loading " << file << std::endl;
		return false;
	}

	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);

	glBegin(GL_QUADS);

	for(j=SCENE_HEIGHT-1;j>=0;j--) {
		px=0;
		py=(j*TILE_SIZE);

		std::string line;
		getline(ifs, line);
		for(i=0;i<SCENE_WIDTH;i++) {
			tile = line[i];
			if(tile==' ') {
				map[j][i] = 0;
			} else {
				map[j][i] = tile - '0';

			coordx_tile = double(map[j][i] % TILESET_WIDTH) / (TILESET_WIDTH);
			coordy_tile = double(map[j][i] / TILESET_WIDTH) / (TILESET_HEIGHT);
			// if (map[j][i] & 1) coordx_tile = 0.0f;
			// else coordx_tile = 0.5f;
			// if (map[j][i] < 3) coordy_tile = 0.0f;
			// else coordy_tile = 0.5f;
			//
			const double tilesetXPixels = 1./TILESET_WIDTH;
			const double tilesetYPixels = 1./TILESET_HEIGHT;
			//coordx_tile = 0.0;
			//coordy_tile = 0.0;
			//double tilesetXPixels = 0.24;
			//double tilesetYPixels = 0.24;

			// TILE_SIZE = 16, FILE_SIZE = 64.
			// 16 / 64 = 0.26666
			glTexCoord2f(coordx_tile, coordy_tile + tilesetYPixels); 
			glVertex2i(px, py);

			glTexCoord2f(coordx_tile + tilesetXPixels, coordy_tile + tilesetYPixels); 
			glVertex2i(px + TILE_SIZE, py);

			glTexCoord2f(coordx_tile + tilesetXPixels, coordy_tile);
			glVertex2i(px + TILE_SIZE, py + TILE_SIZE);

			glTexCoord2f(coordx_tile, coordy_tile);
			glVertex2i(px, py + TILE_SIZE);

			}
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
