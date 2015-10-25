#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"
#include <iostream>
#include <algorithm>

cBicho::cBicho(void)
{
	seq=0;
	delay=0;

	jumping = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}

void cBicho::SetHitpoints(int hp) {
    hitpoints = hp;
}

int cBicho::GetHitpoints() {
    return hitpoints;
}

void cBicho::SetMaxHitpoints(int hp) {
    max_hitpoints = hp;
}

int cBicho::GetMaxHitpoints() {
    return max_hitpoints;
}

void cBicho::Heal(int hp) {
    hitpoints = std::max(hitpoints, max_hitpoints);
}

void cBicho::Damage(int hp) {
    hitpoints = std::min(0, hitpoints - hp);
}

void cBicho::SetAttack(int attack) {
    this->attack = attack;
}

int cBicho::GetAttack() {
    return attack;
}

bool cBicho::IsDead() {
    return hitpoints <= 0;
}

bool cBicho::Collides(cRect *rc)
{
	return ((x>rc->left) && (x+w<rc->right) && (y>rc->bottom) && (y+h<rc->top));
}

bool cBicho::CollidesMap(int *map) {
    int init_tile_x = x / TILE_SIZE;
    int init_tile_y = y / TILE_SIZE;
    int tile_width = w / TILE_SIZE;
    int tile_height = h / TILE_SIZE;
    int end_tile_x = init_tile_x + tile_width + ((x%TILE_SIZE) != 0);
    int end_tile_y = init_tile_y + tile_height + ((y%TILE_SIZE) != 0);

    for (int i = init_tile_x; i < end_tile_x; ++i) {
        if (i < 0 || i >= SCENE_WIDTH) {
            continue;
        }
        for (int j = init_tile_y; j < end_tile_y; ++j) {
            if (j < 0 || j >= SCENE_HEIGHT) {
                continue;
            }
            if (map[i + j*SCENE_WIDTH] != 0) {
                return true;
            }
        }
    }
    return false;
}
bool cBicho::CollidesMapWall(int *map,bool right)
{
	int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if(right)	tile_x += width_tiles;
	
	for(j=0;j<height_tiles;j++)
	{
		if(map[ tile_x + ((tile_y+j)*SCENE_WIDTH) ] != 0)	return true;
	}
	
	return false;
}

bool cBicho::CollidesMapFloor(int *map)
{
	int tile_x,tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if( (x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i=0;
	while((i<width_tiles) && !on_base)
	{
		if( (y % TILE_SIZE) == 0 )
		{
			if(map[ (tile_x + i) + ((tile_y - 1) * SCENE_WIDTH) ] != 0)
				on_base = true;
		}
		else
		{
			if(map[ (tile_x + i) + (tile_y * SCENE_WIDTH) ] != 0)
			{
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}

void cBicho::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;
}
void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo + (BLOCK_SIZE - TILE_SIZE);

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cBicho::MoveDown(int *map) {
    int yaux;
	
	//Whats next tile?
	if( (y % TILE_SIZE) == 0)
	{
		yaux = y;
		y -= STEP_LENGTH;

		if(CollidesMap(map))
		{
			y = yaux;
			state = STATE_LOOKDOWN;
		}
	}
	//Advance, no problem
	else
	{
		y -= STEP_LENGTH;
		if(state != STATE_WALKDOWN)
		{
			state = STATE_WALKDOWN;
			seq = 0;
			delay = 0;
		}
	}
}

void cBicho::MoveLeft(int *map)
{
	int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if(CollidesMap(map))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		if(state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}

void cBicho::MoveUp(int *map) {
    int yaux;

	//Whats next tile?
	if( (y % TILE_SIZE) == 0)
	{
		yaux = y;
		y += STEP_LENGTH;

		if(CollidesMap(map))
		{
			y = yaux;
			state = STATE_LOOKUP;
		}
	}
	//Advance, no problem
	else
	{
		y += STEP_LENGTH;

		if(state != STATE_WALKUP)
		{
			state = STATE_WALKUP;
			seq = 0;
			delay = 0;
		}
	}
}

void cBicho::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMap(map))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if(state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}

void cBicho::Stop()
{
	switch(state)
	{
        case STATE_WALKDOWN:  state = STATE_LOOKDOWN;  break;
        case STATE_WALKLEFT:  state = STATE_LOOKLEFT;  break;
        case STATE_WALKUP:    state = STATE_LOOKUP;    break;
		case STATE_WALKRIGHT: state = STATE_LOOKRIGHT; break;
	}
}

void cBicho::Logic(int *map)
{
}

void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}

