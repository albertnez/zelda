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

void cPlayer::Draw(int tex_id, int texWidth, int texHeight)
{	
	float xo,yo,xf,yf;

	animations[currentAnimation].CurrentFrame().TextureOffset(xo, yo, xf, yf, texWidth, texHeight);
	if (state == State::Walk) {
		animations[currentAnimation].Advance(1);
	}
	DrawRect(tex_id,xo,yo,xf,yf);
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
