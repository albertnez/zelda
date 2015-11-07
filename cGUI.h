#pragma once

#include "Globals.h"
#include "cFont.h"
#define SCENE_Xo 0
#define SCENE_Yo 176




class cGUI
{
private:
	int hp;
	int maxHP;
	int view_xo;
	int view_yo;
	int pos_x;
	int pos_y;
	int max_views_x;
	int max_views_y;
	cFont Font;
public:
	cGUI();
	~cGUI();
	void init();
	void setHP(int newHP);
	void setMaxHP(int newMaxLife);
	void setXo(int newXo);
	void setYo(int newYo);
	void setViewY(int newXo);
	void setMaxViewsX(int viewsX);
	void setMaxViewsY(int viewsY);
	void setViewX(int newYo);
	void Draw(int img, int font, int gui_width, int gui_height);
	void DrawPlainRect(float r, float g, float b, int x, int y, int w, int h);
	void DrawRect(
		int tex_id, float xo, float yo,
		float xf, float yf, int x, int y, int w, int h);
	void DrawText(int font, std::string text, int x, int y);
	void DrawMap(int level, int x, int y);
};

