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
    void SpecificDraw(int texId, int texWidth, int texHeight) override;
    void SetAnimation(const std::string &name);
    void SetScene(int sceneX, int sceneY);
    void SetLevel(int level);

    void PickUp();
    void UseKey();
    int getKeyCount();
    ObjectType getEquippedObjectA();
    ObjectType getEquippedObjectB();


private:
    void InDungeonDoor() override;

	Direction transition;
    bool isAttacking;
    int attackTime;
    bool overworld;
    int sceneX;
    int sceneY;
    int level;

    std::string swordAnimation;
    std::unordered_map<std::string, cAnim> swordAnimations;

    // When attack / stop attacking, from which animation to which go.
    static const std::unordered_map<std::string,std::string> nextAttackAnim;
    static const std::unordered_map<std::string,std::pair<int,int>> swordOffset;
    static const int maxAttackTime;

    int keys;
};
