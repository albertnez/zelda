#pragma once

#include "cBicho.h"
#include "cAnim.h"
#include "cObject.h"
#include "cKey.h"
#include <unordered_map>
#include <string>
#include <memory>



class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	bool ReachLimit(Direction dir) override;
	bool IsChangingScreen() const;
	void EndTransition();
	Direction GetTransition() const;
    void Attack();
    bool IsAttacking() const;
    void SpecificLogic(const cMap &map) override;
    cRect GetSwordArea() const;
    void DrawSword(int texId, int texWidth, int texHeight) const;
    void SetAnimation(const std::string &name);

    void PickUp();


private:
	Direction transition;
    bool isAttacking;
    int attackTime;

    std::string swordAnimation;
    std::unordered_map<std::string, cAnim> swordAnimations;

    // When attack / stop attacking, from which animation to which go.
    static const std::unordered_map<std::string,std::string> nextAttackAnim;
    static const std::unordered_map<std::string,std::pair<int,int>> swordOffset;
    static const int maxAttackTime;

    int keys;
};
