#include "cPlayer.h"
#include "cScene.h"

const std::unordered_map<std::string,std::string> cPlayer::nextAttackAnim {
    {"up", "attackup"},
    {"attackup", "up"},
    {"down", "attackdown"},
    {"attackdown", "down"},
    {"left", "attackleft"},
    {"attackleft", "left"},
    {"right", "attackright"},
    {"attackright", "right"},
};
const int cPlayer::maxAttackTime{15};

cPlayer::cPlayer() 
    : transition(Direction::None),
      isAttacking(false),
      attackTime(0) {
	animations = LoadAnimations("res/link.anim");
	currentAnimation = "down";
}
cPlayer::~cPlayer(){}

bool cPlayer::ReachLimit(Direction dir) {
	transition = dir;
	return true;
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

void cPlayer::Attack() {
    if (isAttacking) {
        return;
    }
    isAttacking = true;
    SetAnimation(nextAttackAnim.at(GetAnimation()));
    attackTime = 0;
}

bool cPlayer::IsAttacking() {
    return isAttacking;
}

void cPlayer::SpecificLogic(const cMap &map) {
    if (isAttacking && ++attackTime > maxAttackTime) {
        isAttacking = false;
        SetAnimation(nextAttackAnim.at(GetAnimation()));
    }
}
