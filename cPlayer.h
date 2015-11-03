#pragma once

#include "cBicho.h"
#include "cAnim.h"
#include <unordered_map>
#include <string>

extern const int PLAYER_TILE_SIZE;

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void ReachLimit(Direction dir) override;
	void Draw(int tex_id, int texWidth, int texHeight);
	bool IsChangingScreen();
	void EndTransition();
	Direction GetTransition();

private:
	Direction transition;
};
