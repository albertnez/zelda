#pragma once

#include "cBicho.h"

extern const int PLAYER_TILE_SIZE;

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
