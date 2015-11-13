#include "cGUI.h"

const int VIEW_WIDTH = 16;
const int VIEW_HEIGHT = 11;
const int SPRITES_HEIGHT = 64;
const int SPRITES_WIDTH = 256;

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


void cGUI::setEquippedObjectA(int object) {
    equippedObjectA = object;
}

void cGUI::setEquippedObjectB(int object) {
    equippedObjectB = object;
}

void cGUI::setKeyCount(int keys) {
    keyCount = keys;
}




void cGUI::Draw(int img, int font, int sprites, int gui_width, int gui_height)
{
    DrawPlainRect(0.0f, 0.0f, 0.0f,
        0, SCENE_Yo, gui_width, gui_height-SCENE_Yo);

    int resthp = hp;
    int y = 10;
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
        
        DrawRect(img, xo, yo, xf, yf, x_heart, y+SCENE_Yo, 8, 8);
        resthp -= 2;
    }
    std::string text = "-LIFE-";
    glColor3f(1.0f, 0.0f, 0.0f);
    DrawText(font, text, x, y+16+SCENE_Yo);
    glColor3f(1.0f, 1.0f, 1.0f);
    x = 16;
    y = 8;
    DrawMap(0,x,y);
    x = 120;
    y = 8;
    DrawObjects(sprites, x, y);
    x = 90;
    y = 8;
    DrawCounters(sprites, font, x, y);
}

void cGUI::DrawObjects(int sprites, int x, int y) {
    int w = 22;
    int h = 36;
    float xo = 0.0f;
    float yf = 0.0f;
    float xf = float(w) / SPRITES_WIDTH;
    float yo = float(h) / SPRITES_HEIGHT;
    DrawRect(sprites, xo, yo, xf, yf, x, y+SCENE_Yo, w, h);
    x = x + 23;
    xo = xf;
    xf = xo + float(w) / SPRITES_WIDTH;
    DrawRect(sprites, xo, yo, xf, yf, x, y+SCENE_Yo, w, h);

}

void cGUI::DrawCounters(int sprites, int font, int x, int y) {
    int w = 9;
    int h = 9;
    float xo = 125.0f/SPRITES_WIDTH;
    float xf = xo + float(w) / SPRITES_WIDTH;
    float yo = float(h) / SPRITES_HEIGHT;
    float yf = 0.0f;
    DrawRect(sprites, xo, yo, xf, yf, x, y+SCENE_Yo, w, h);
    std::string s;
    s = 'X'+ std::to_string(keyCount);
    DrawText(font, s, x + w, y + SCENE_Yo);
}


void cGUI::DrawText(int font, std::string text, int x, int y) {
    for (int i = 0; i < text.length(); ++i) {
        float xo, yo, xf, yf;
        Font.getCharPosition(text[i], xo, yo, xf, yf);
        int x_letter = x + i * 9;
        DrawRect(font, xo, yo, xf, yf, x_letter, y, 8, 8);
    }
}

void cGUI::DrawTextWorld(int font, std::string text, int x, int y) {
    for (int i = 0; i < text.length(); ++i) {
        float xo, yo, xf, yf;
        Font.getCharPosition(text[i], xo, yo, xf, yf);
        int x_letter = x + i * 9;
        DrawRectWorld(font, xo, yo, xf, yf, x_letter, y, 8, 8);
    }
}

void cGUI::DrawMap(int level, int x, int y) {
    int mapWidth = 64;
    int mapHeight = 32;
    DrawPlainRect(0.5f, 0.5f, 0.5f, x, y+SCENE_Yo, mapWidth, mapHeight);
    int viewX = ((2 * pos_x + 1)*mapWidth / max_views_x) / 2 - 2;
    int viewY = ((2*pos_y + 1)*mapHeight / max_views_y) / 2 - 2;
    DrawPlainRect(0.0f, 1.0f, 0.0f, x+viewX, y+viewY + SCENE_Yo, 4, 4);
}

void cGUI::DrawPlainRect(float r, float g, float b,
    int x, int y, int w, int h) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    int screen_x = x + view_xo;
    int screen_y = y + view_yo;

    glVertex2i(screen_x , screen_y);
    glVertex2i(screen_x + w, screen_y);
    glVertex2i(screen_x + w, screen_y + h);
    glVertex2i(screen_x, screen_y + h);
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
    glTexCoord2f(xo, yo);    glVertex2i(screen_x, screen_y);
    glTexCoord2f(xf, yo);    glVertex2i(screen_x + w, screen_y);
    glTexCoord2f(xf, yf);    glVertex2i(screen_x + w, screen_y + h);
    glTexCoord2f(xo, yf);    glVertex2i(screen_x, screen_y + h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void cGUI::DrawRectWorld(
    int tex_id, float xo, float yo, float xf, float yf,
    int x, int y, int w, int h)
{
    int screen_x, screen_y;
    screen_x = x;
    screen_y = y;
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_id);
    glBegin(GL_QUADS);
    glTexCoord2f(xo, yo);    glVertex2i(screen_x, screen_y);
    glTexCoord2f(xf, yo);    glVertex2i(screen_x + w, screen_y);
    glTexCoord2f(xf, yf);    glVertex2i(screen_x + w, screen_y + h);
    glTexCoord2f(xo, yf);    glVertex2i(screen_x, screen_y + h);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void cGUI::DrawTitle(int tex, int game_width, int game_height) {
    DrawRect(tex, 0.0f, 1.0f, 1.0f, 0.0f, 0, 0, game_width, game_height);
}

void cGUI::DrawGameOver(int tex, int game_width, int game_height) {
    DrawText(tex, "GAME OVER", game_width/2-40, game_height/2-4);
}

void cGUI::DrawInstructions(int tex, int game_width, int game_height) {
    std::string s;
    s = "MOVE: arrow keys";
    DrawText(tex, s, game_width / 2 - s.length()*4.5, game_height / 2 + 22);
    s = "A BUTTON: ??????";
    DrawText(tex, s, game_width / 2 - s.length()*4.5, game_height / 2 + 13);
    s = "B BUTTON: ??????";
    DrawText(tex, s, game_width / 2 - s.length()*4.5, game_height / 2 + 4);
    s = "START: return key";
    DrawText(tex, s, game_width / 2 - s.length()*4.5, game_height / 2 - 5);
    s = "INSTRUCTIONS: 'h' key";
    DrawText(tex, s, game_width / 2 - s.length()*4.5, game_height / 2 - 14);
    
}
void cGUI::DrawCredits(int font, int sprites, int game_width, int game_height) {
    float xo = 108.0f / float(SPRITES_WIDTH);
    float xf = xo + 16.0f / float(SPRITES_WIDTH);
    float yo = 16.0f / float(SPRITES_HEIGHT);
    float yf = 0.0f;
    int w = 8;
    int h = 8;

    for (int i = 1; i < 31; ++i) {
        DrawRectWorld(sprites, xo, yo, xf, yf, i*w, game_height-392, w, h);

        //DrawRectWorld(sprites, xo, yo, xf, yf, i*w, 8, w, h);
    }
    for (int i = 1; i < 13; ++i) {
        DrawRectWorld(sprites, xo, yo, xf, yf, i*w, game_height/2, w, h);
        DrawRectWorld(sprites, xo, yo, xf, yf, (31-i)*w, game_height / 2, w, h);
    }
    for (int i = game_height - 392; i < game_height / 2
        ; i+=8) {
        DrawRectWorld(sprites, xo, yo, xf, yf, 8, i, w, h);
        DrawRectWorld(sprites, xo, yo, xf, yf, 240, i, w, h);
    }
    std::string s;
    s = "STAFF";
    DrawText(font, s, game_width / 2 - s.length()*4.5+1, game_height / 2);
    s = "Albert Martinez";
    DrawText(font, s, game_width / 2 - s.length()*4.5, game_height / 2 - 72);
    s = "Alicia Nicas";
    DrawText(font, s, game_width / 2 - s.length()*4.5, game_height / 2 - 136);
}