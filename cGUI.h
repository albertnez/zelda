#pragma once

#include "Globals.h"
#include "cFont.h"
#include "cObject.h"
#include <unordered_map>

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
    ObjectType equippedObjectA;
    ObjectType equippedObjectB;
    int keyCount;
    cFont Font;
    int level;
    int money;
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
    void setEquippedObjectA(ObjectType object);
    void setEquippedObjectB(ObjectType object);
    void setKeyCount(int keys);
    void setViewX(int newYo);
    void Draw(int img, int font, int sprites, int gui_width, int gui_height);
    void DrawObjects(int sprites, int x, int y);
    void DrawCounters(int sprites, int font, int x, int y);
    void DrawPlainRect(float r, float g, float b, int x, int y, int w, int h);
    void DrawRect(
        int tex_id, float xo, float yo,
        float xf, float yf, int x, int y, int w, int h);
    void DrawRectWorld(int tex_id, float xo, float yo, float xf, float yf, int x, int y, int w, int h);
    void DrawTitle(int tex, int game_width, int game_height);
    void DrawGameOver(int tex, int game_width, int game_height);
    void DrawInstructions(int tex, int game_width, int game_height);
    void DrawCredits(int font, int sprites, int game_width, int game_height);
    void DrawText(int font, std::string text, int x, int y);
    void DrawTextWorld(int font, std::string text, int x, int y);
    void DrawMap(int font, int x, int y);
    void setLevel(int lvl);
    void SetMoney(int amount);
};

