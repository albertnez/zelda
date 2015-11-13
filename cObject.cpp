#include "cObject.h"

const int OBJECT_WIDTH = 16;
const int OBJECT_HEIGHT = 16;

cObject::cObject(ObjectType type, int posx, int posy, int width, int height,
                 float texxo, float texyo, float texxf, float texyf)
    : type(type),
      x(posx),
      y(posy),
      w(width),
      h(height),
      xo(texxo),
      yo(texyo),
      xf(texxf),
      yf(texyf) {}

cObject::~cObject()
{
}


void cObject::Draw(int tex_id) {
    DrawRect(tex_id, xo, yo, xf, yf, x, y);
}
bool cObject::Collides(cRect pRect) {
    return ((y + h) > pRect.bottom) && (y < pRect.top) &&
        (x + w > pRect.left) && (x < pRect.right);
}

void cObject::DrawRect(
    int tex_id, float xo, float yo, float xf, float yf,
    int x, int y)
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

ObjectType cObject::GetType() const {
    return type;
}
