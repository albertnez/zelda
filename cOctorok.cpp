#include "cOctorok.h"

const int cOctorok::width = 16;
const int cOctorok::height = 16;
const int cOctorok::step = 1;
const std::vector<Direction> cOctorok::nextDir {
	Direction::Left,   // From None to left.
	Direction::Right,  // From Up to right.
	Direction::Left,   // From Down to left.
	Direction::Up,     // From Left to up.
	Direction::Down,   // From Right to down.
};


cOctorok::cOctorok() : sceneX(-1), sceneY(-1) {
	Init();
}

cOctorok::cOctorok(int x, int y, int sceneX, int sceneY) 
	: cBicho(x, y, width, height),
	sceneX(sceneX), sceneY(sceneY) {
	Init();
}

void cOctorok::SpecificLogic(const cMap &map) {
	if (!Move(map, direction, sceneX, sceneY)) {
		direction = nextDir[int(direction)];
		SetAnimation(to_string(direction));
	}
}

void cOctorok::Init() {
	animations = LoadAnimations("res/octorok.anim");
	currentAnimation = "down";
    SetHitpoints(2);
	w = width;
	h = height;
	stepLength = step;
	attack = 1;
}


