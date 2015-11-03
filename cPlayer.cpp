#include "cPlayer.h"
#include "cScene.h"

const int PLAYER_TILE_SIZE = 2;
cPlayer::cPlayer() : transition(Direction::None) {
	animations = LoadAnimations("res/link.anim");
	currentAnimation = "up";
}
cPlayer::~cPlayer(){}

void cPlayer::ReachLimit(Direction dir) {
	transition = dir;
}

void cPlayer::Draw(int tex_id, int texWidth, int texHeight)
{	
	float xo,yo,xf,yf;

	animations[currentAnimation].CurrentFrame().TextureOffset(xo, yo, xf, yf, texWidth, texHeight);
	animations[currentAnimation].Advance(2);

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
