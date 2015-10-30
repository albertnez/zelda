
#include "cPlayer.h"

cPlayer::cPlayer() : transition(Direction::None), scene_x(0), scene_y(0) {}
cPlayer::~cPlayer(){}

void cPlayer::ReachLimit(Direction dir) {
	transition = dir;
}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;

	switch(GetState())
	{
		//1
        case STATE_LOOKDOWN:
		case STATE_LOOKLEFT:	xo = 0.0f;	yo = 0.25f;
								break;
		//4
        case STATE_LOOKUP:
		case STATE_LOOKRIGHT:	xo = 0.25f;	yo = 0.25f;
								break;
		//1..3
        case STATE_WALKDOWN:
		case STATE_WALKLEFT:	xo = 0.0f;	yo = 0.25f + (GetFrame()*0.25f);
								NextFrame(3);
								break;
		//4..6
        case STATE_WALKUP:
		case STATE_WALKRIGHT:	xo = 0.25f; yo = 0.25f + (GetFrame()*0.25f);
								NextFrame(3);
								break;
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
			--scene_x;
			break;
		case Direction::Right:
			++scene_x;
			break;
		case Direction::Up:
			++scene_y;
			break;
		case Direction::Down:
			--scene_y;
			break;
		default:
			break;
	}
	transition = Direction::None;
}

Direction cPlayer::GetTransition() {
	return transition;
}
