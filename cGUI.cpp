#include "cGUI.h"



cGUI::cGUI()
{
	view_xo = 0;
	view_yo = 0;

}


cGUI::~cGUI()
{
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

void cGUI::Draw(int img, int gui_width, int gui_height)
{
	int x = glutGet(GL_COLOR);

	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2i(view_xo, view_yo+SCENE_Yo);
	glVertex2i(view_xo+gui_width, view_yo+SCENE_Yo);
	glVertex2i(view_xo+gui_width, view_yo+gui_height);
	glVertex2i(view_xo, view_yo+gui_height);
	glEnd();

	glColor3f(1.0f, 1.0f, 1.0f);

	//glScissor(0, SCENE_Yo, gui_width,gui_height-SCENE_Yo);
	//glClear(GL_COLOR_BI)
	int resthp = hp;
	int y = SCENE_Yo+10;
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
		int x = 175 + 9*i/2;
		
		DrawRect(img, xo, yo, xf, yf, x, y, 8, 8);
		resthp -= 2;
	}
}

void cGUI::DrawRect(
	int tex_id, float xo, float yo, float xf, float yf,
	int x, int y, int w, int h)
{


	int screen_x, screen_y;

	screen_x = x + view_xo;
	screen_y = y + view_yo;
	//glColor3f(1.0f, 0.0f, 0.0f);
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
