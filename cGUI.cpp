#include "cGUI.h"

const int VIEW_WIDTH = 16;
const int VIEW_HEIGHT = 11;

cGUI::cGUI()
{
	view_xo = 0;
	view_yo = 0;

}


cGUI::~cGUI()
{
}

void cGUI::init() {
	Font = cFont();
	Font.loadFont();
}

void cGUI::setHP(int newHP) {
	hp = newHP;
}

void cGUI::setMaxHP(int newMaxLife) {
	maxHP = newMaxLife;
}

void cGUI::setXo(int newXo) {
	view_xo = newXo;
}

void cGUI::setYo(int newYo) {
	view_yo = newYo;
}

void cGUI::setViewX(int newXo) {
	pos_x = newXo;
}

void cGUI::setViewY(int newYo) {
	pos_y = newYo;
}

void cGUI::setMaxViewsX(int viewsX) {
	max_views_x = viewsX;
}

void cGUI::setMaxViewsY(int viewsY) {
	max_views_y = viewsY;
}


void cGUI::Draw(int img, int font, int gui_width, int gui_height)
{
	DrawPlainRect(0.0f, 0.0f, 0.0f,
		0, 0, gui_width, gui_height-SCENE_Yo);

	int resthp = hp;
	int y = SCENE_Yo+10;
	int x = 175;
	for (int i = 0; i < maxHP; i += 2) {
		float xo;
		
		if (resthp <= 0) {
			xo = 0.4375f;
		}
		else if (resthp == 1) {
			xo = 0.21875f;
		}
		else {
			xo = 0.0f;
		}
		float yo = 0.25f;
		float yf = 0.0f;
		float xf = xo + 0.21875f;
		//screencoords
		int x_heart = x + 9*i/2;
		
		DrawRect(img, xo, yo, xf, yf, x_heart, y, 8, 8);
		resthp -= 2;
	}
	std::string text = "-LIFE-";
	DrawText(font, text, x, y+16);
	x = 16;
	y = 8;
	DrawMap(0,x,y);
}

void cGUI::DrawText(int font, std::string text, int x, int y) {
	for (int i = 0; i < text.length(); ++i) {
		float xo, yo, xf, yf;
		Font.getCharPosition(text[i], xo, yo, xf, yf);
		int x_letter = x + i * 9;
		DrawRect(font, xo, yo, xf, yf, x_letter, y, 8, 8);
	}
}

void cGUI::DrawMap(int level, int x, int y) {
	int mapWidth = 64;
	int mapHeight = 32;
	DrawPlainRect(0.5f, 0.5f, 0.5f, x, y, mapWidth, mapHeight);
	int viewX = ((2 * pos_x + 1)*mapWidth / max_views_x) / 2 - 2;
	int viewY = ((2*pos_y + 1)*mapHeight / max_views_y) / 2 - 2;
	DrawPlainRect(0.0f, 1.0f, 0.0f, x+viewX, y+viewY, 4, 4);
}

void cGUI::DrawPlainRect(float r, float g, float b,
	int x, int y, int w, int h) {
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	int screen_x = x + view_xo;
	int screen_y = y + view_yo;

	glVertex2i(screen_x , screen_y + SCENE_Yo);
	glVertex2i(screen_x + w, screen_y + SCENE_Yo);
	glVertex2i(screen_x + w, screen_y + SCENE_Yo + h);
	glVertex2i(screen_x, screen_y + SCENE_Yo + h);
	glEnd();
	glColor3f(1.0f, 1.0f, 1.0f);
}


void cGUI::DrawRect(
	int tex_id, float xo, float yo, float xf, float yf,
	int x, int y, int w, int h)
{


	int screen_x, screen_y;

	screen_x = x + view_xo;
	screen_y = y + view_yo;
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y + h);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
