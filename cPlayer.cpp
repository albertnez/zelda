
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

	switch (GetDirection()) {
		case Up:
			xo = 0.25f;
			yo = 0.25f;
			break;
		case Down: 
			xo = 0.0f;
			yo = 0.25f;
			break;
		case Left:
			xo = 0.0f;
			yo = 0.25f;
			break;
		case Right:
			xo = 0.25f;
			yo = 0.25f;
			break;
		default:
			// Set some default sprite.
			xo = 0.25f;
			yo = 0.25f;
			break;
	}
	if (GetState() == State::Walk) {
		yo += GetFrame()*0.25f;
		NextFrame(3);
	}
	xf = xo + 0.25f;
	yf = yo - 0.25f;

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
