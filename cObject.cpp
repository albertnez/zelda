#include "cObject.h"

const int OBJECT_WIDTH = 16;
const int OBJECT_HEIGHT = 16;

cObject::cObject()
{
}

cObject::cObject(int posx, int posy, float texxo, float texyo,
    float texxf, float texyf){

    x = posx;
    y = posy;
    xo = texxo;
    yo = texyo;
    xf = texxf;
    yf = texyf;
}


cObject::~cObject()
{
}


void cObject::Draw(int tex_id) {
    DrawRect(tex_id, xo, yo, xf, yf, x, y, 16, 16);
}
bool cObject::Collides(cRect pRect) {
    return ((y + OBJECT_HEIGHT) > pRect.bottom) && (y < pRect.top) &&
        (x + OBJECT_WIDTH > pRect.left) && (x < pRect.right);
}

void cObject::DrawRect(
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

