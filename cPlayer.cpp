#include "cPlayer.h"
#include "cScene.h"

const int PLAYER_TILE_SIZE = 2;
cPlayer::cPlayer() : transition(Direction::None) {
	animations = LoadAnimations("res/link.anim");
	currentAnimation = "down";
}
cPlayer::~cPlayer(){}

bool cPlayer::ReachLimit(Direction dir) {
	transition = dir;
	return true;
}

bool cPlayer::IsChangingScreen() 
{
	return transition != None;
}

void cPlayer::EndTransition() {
	transition = Direction::None;
}

Direction cPlayer::GetTransition() {
	return transition;
}
