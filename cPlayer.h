#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void ReachLimit(Direction dir) override;
	void Draw(int tex_id);
	bool IsChangingScreen();
	void EndTransition();
	Direction GetTransition();

private:
	Direction transition;
};
