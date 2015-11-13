#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"
#include <iostream>
#include <algorithm>

const int FRAME_DELAY = 8;
const int STEP_LENGTH = 2;

cBicho::cBicho(void) {
    Init();
}

cBicho::~cBicho(void) {}

cBicho::cBicho(int posx,int posy,int width,int height)
    : x(posx),
      y(posy),
      w(width),
      h(height) {
    Init();
}

void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy) const
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty) const
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height) const
{
	*width = w;
	*height = h;
}

void cBicho::SetHitpoints(int hp) {
    hitpoints = hp;
}

int cBicho::GetHitpoints() const {
    return hitpoints;
}

void cBicho::SetMaxHitpoints(int hp) {
    maxHitpoints = hp;
}

int cBicho::GetMaxHitpoints() const {
    return maxHitpoints;
}

void cBicho::Heal(int hp) {
    hitpoints = std::max(hitpoints, maxHitpoints);
}

bool cBicho::Damage(int hp) {
    if (isProtected) return false;
    hitpoints = std::max(0, hitpoints - hp);
    if (hitpoints > 0) {
        isProtected = true;
    }
    return true;
}

void cBicho::SetAttack(int attack) {
    this->attack = attack;
}

int cBicho::GetAttack() const {
    return attack;
}

bool cBicho::IsDead() const {
    return hitpoints <= 0;
}

bool cBicho::Collides(const cRect &rect) {
    return (y + h > rect.bottom) && (y < rect.top) &&
           (x + w > rect.left) && (x < rect.right);
}

bool cBicho::CollidesMap(const cMap &map) {
    int init_tile_x = x / TILE_SIZE;
    int init_tile_y = y / TILE_SIZE;
    int tile_width = w / TILE_SIZE;
    int tile_height = h / TILE_SIZE;
    int end_tile_x = init_tile_x + tile_width + ((int(x)%TILE_SIZE) != 0);
    int end_tile_y = init_tile_y + tile_height + ((int(y)%TILE_SIZE) != 0);

    for (int i = init_tile_x; i < end_tile_x; ++i) {
        if (i < 0 || i >= map.Width()) {
            continue;
        }
        for (int j = init_tile_y; j < end_tile_y; ++j) {
            if (j < 0 || j >= map.Height()) {
                continue;
            }
	    if (map.Obstacle(i, j)) {
                return true;
            }
        }
    }
    return false;
}

bool cBicho::ReachesMapLimit(const cMap &map, int scene_x, int scene_y) {
	int init_tile_x = x / TILE_SIZE;
	int init_tile_y = y / TILE_SIZE;
	int tile_width = w / TILE_SIZE;
	int tile_height = h / TILE_SIZE;
	int end_tile_x = init_tile_x + tile_width + ((int(x)%TILE_SIZE) != 0);
	int end_tile_y = init_tile_y + tile_height + ((int(y)%TILE_SIZE) != 0);
	int start_x = VIEW_WIDTH * scene_x;
	int start_y = VIEW_HEIGHT * scene_y;
	
    return (init_tile_x < start_x 
	    || init_tile_y < start_y 
	    || end_tile_x > start_x + VIEW_WIDTH 
	    || end_tile_y > start_y + VIEW_HEIGHT);
}
// By default, enemies cannot go through.
bool cBicho::ReachLimit(Direction dir) {
	return false;
}

void cBicho::ResetAnimation() {
	animations[currentAnimation].Reset();
}

void cBicho::SetAnimation(const std::string& name) {
	currentAnimation = name;
	animations[currentAnimation].Reset();
}

std::string cBicho::GetAnimation() const {
	return currentAnimation;
}

cRect cBicho::GetArea() const {
    cRect rc;
    rc.left   = x;
    rc.right  = x+w;
    rc.bottom = y;
    rc.top    = y+h;
    return rc;
}

void cBicho::Draw(int texId, int texWidth, int texHeight) {
    SpecificDraw(texId, texWidth, texHeight);
	float xo,yo,xf,yf;

	animations[currentAnimation].CurrentFrame().TextureOffset(xo, yo, xf, yf, texWidth, texHeight);
	if (state == State::Walk) {
		animations[currentAnimation].Advance(1);
	}
	DrawRect(texId,xo,yo,xf,yf);
}

void cBicho::SpecificDraw(int texId, int texWidth, int texHeight) {
}

void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;

	screen_x = x;
	screen_y = y;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);

        float alpha = 1.0;
        if (isProtected && (protectionTime % 20) < 10) {
            alpha = 0.2;
        }

        glColor4f(1.0, 1.0, 1.0, alpha);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

bool cBicho::Move(const cMap& map, Direction dir, int sceneX, int sceneY) {
	float &axis = (dir == Direction::Left || dir == Direction::Right) ? x : y;
	int mult = 1;
	bool canMove = true;
	if (dir == Direction::Left || dir == Direction::Down) {
		mult = -1;
	}
	// What's next tile
	if (int(axis) % TILE_SIZE == 0) {
		int aux = axis;
		axis += stepLength * mult;
		if (ReachesMapLimit(map, sceneX, sceneY)) {
			canMove = ReachLimit(dir);
			axis = aux;
		} else if (CollidesMap(map)) {
			axis = aux;
			state = State::Look;
			canMove = false;
		}
	} else {
		// Advance
		axis += stepLength * mult;
	}
	// Always set direction
	direction = dir;
	if (canMove && state != State::Walk) {
		state = State::Walk;
	}
    // Calculate if entering DungeonDoor from below.
    int cellx = x/TILE_SIZE;
    int celly = y/TILE_SIZE;
    if (!ReachesMapLimit(map, sceneX, sceneY) && map.DungeonDoor(cellx, celly)) {
        InDungeonDoor();
    }

	return canMove;
}

void cBicho::Stop() {
	state = State::Look;
}

void cBicho::Logic(const cMap &map) {
    UpdateProtected();
    SpecificLogic(map);
}

void cBicho::SpecificLogic(const cMap &map) {
}

void cBicho::NextFrame(int max) {
	animations[currentAnimation].Advance(max);
}


Direction cBicho::GetDirection() const {
	return direction;
}

void cBicho::SetDirection(Direction dir) {
	direction = dir;
}

cBicho::State cBicho::GetState() const {
	return state;
}

void cBicho::SetState(cBicho::State state) {
	this->state = state;
}

void cBicho::UpdateProtected() {
    if (!isProtected) return;
    if (++protectionTime > maxProtectionTime) {
        isProtected = false;
        protectionTime = 0;
    }
}

void cBicho::InDungeonDoor() {
}

void cBicho::Init() {
    stepLength = STEP_LENGTH;
    state = State::Walk;
    direction = Direction::Down;
    isProtected = false;
    protectionTime = 0;
    maxProtectionTime = 30;
    hitpoints = 0;
    maxHitpoints = 0;
}
