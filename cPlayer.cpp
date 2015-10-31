
#include "cPlayer.h"
#include "cScene.h"

cPlayer::cPlayer() : transition(Direction::None) {}
cPlayer::~cPlayer(){}

void cPlayer::ReachLimit(Direction dir) {
	transition = dir;
}

void cPlayer::Draw(int tex_id)
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

	DrawRect(tex_id,xo,yo,xf,yf);
}


bool cPlayer::IsChangingScreen() 
{
	return transition != None;
}

void cPlayer::EndTransition() {
	switch (transition) {
		case Direction::Left:
			x -= 2*TILE_SIZE;
			break;
		case Direction::Right:
			x += 2*TILE_SIZE;
			break;
		case Direction::Up:
			y += 2*TILE_SIZE;
			break;
		case Direction::Down:
			y -= 2*TILE_SIZE;
			break;
		default:
			break;
	}
	transition = Direction::None;
}

Direction cPlayer::GetTransition() {
	return transition;
}
