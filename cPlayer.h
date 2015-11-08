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

    bool ReachLimit(Direction dir) override;
    bool IsChangingScreen();
    void EndTransition();
    Direction GetTransition();

private:
    Direction transition;
};
