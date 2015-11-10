#pragma once

#include "cBicho.h"
#include "cAnim.h"
#include <unordered_map>
#include <string>

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	bool ReachLimit(Direction dir) override;
	bool IsChangingScreen();
	void EndTransition();
	Direction GetTransition();
    void Attack();
    bool IsAttacking();
    void SpecificLogic(const cMap &map) override;

private:
	Direction transition;
    bool isAttacking;
    int attackTime;

    // When attack / stop attacking, from which animation to which go.
    static const std::unordered_map<std::string,std::string> nextAttackAnim;
    static const int maxAttackTime;
};
