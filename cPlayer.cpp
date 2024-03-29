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

const std::unordered_map<std::string,std::pair<int,int>> cPlayer::swordOffset {
    {"up", {3, 14}},
    {"down", {6, -14}},
    {"left", {-14, 3}},
    {"right", {14, 3}},
};
const int cPlayer::maxAttackTime{15};

cPlayer::cPlayer() 
    : transition(Direction::None),
      isAttacking(false),
      attackTime(0),
      overworld(true),
      sceneX(0),
      sceneY(0),
      level(2),
      money(0) {
    SetAttack(1);
    maxProtectionTime = 60;
    animations = LoadAnimations("res/link.anim");
    currentAnimation = "down";
    swordAnimations = LoadAnimations("res/sword.anim");
    swordAnimation = currentAnimation;
    EnableDyingAnimation(false);  // Disable dying animation.
    keys = 0;
}
cPlayer::~cPlayer(){}

bool cPlayer::ReachLimit(Direction dir) {
    if (level == 3 && sceneX == 0 && sceneY == 0&&dir==Direction::Down) {
        transition = Direction::Above;
        return true;
    }
	transition = dir;
	return true;
}

bool cPlayer::IsChangingScreen() const {
	return transition != None;
}

void cPlayer::EndTransition() {
	transition = Direction::None;
}

Direction cPlayer::GetTransition() const { 
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

bool cPlayer::IsAttacking() const {
    return isAttacking;
}

void cPlayer::SpecificLogic(const cMap &map) {
    if (isAttacking && ++attackTime > maxAttackTime) {
        isAttacking = false;
        SetAnimation(nextAttackAnim.at(GetAnimation()));
    }
}

cRect cPlayer::GetSwordArea() const {
    // Treat each direction
    const Frame &frame = swordAnimations.at(swordAnimation).CurrentFrame();
    int xo, yo;
    std::tie(xo, yo) = swordOffset.at(swordAnimation);
    cRect area;
    area.bottom = y + yo;
    area.top = area.bottom + frame.height;
    area.left = x + xo;
    area.right = area.left + frame.width;
    return area;
}

void cPlayer::SpecificDraw(int texId, int texWidth, int texHeight) {
    // If it is attacking, draw the sword before Link.
    if (!isAttacking) {
        return;
    }

    float xo, yo, xf, yf;
    float screen_x = x + swordOffset.at(swordAnimation).first;
    float screen_y = y + swordOffset.at(swordAnimation).second;
    float width = swordAnimations.at(swordAnimation).CurrentFrame().width;
    float height = swordAnimations.at(swordAnimation).CurrentFrame().height;

    swordAnimations.at(swordAnimation).CurrentFrame().TextureOffset(
            xo, yo, xf, yf, texWidth, texHeight);
    
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texId);

    float alpha = 1.0;
    if (isProtected && (protectionTime % 20) < 10) {
        alpha = 0.0;
    }

    glColor4f(1.0, 1.0, 1.0, alpha);
    glBegin(GL_QUADS);	
    glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
    glTexCoord2f(xf,yo);	glVertex2i(screen_x+width,screen_y);
    glTexCoord2f(xf,yf);	glVertex2i(screen_x+width,screen_y+height);
    glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+height);
    glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cPlayer::SetAnimation(const std::string &name) {
    if (swordAnimations.count(name)) {
        swordAnimation = name;
    }
    cBicho::SetAnimation(name);
}


void cPlayer::PickUp() {
    ++keys;
}
void cPlayer::UseKey() {
    --keys;
}

int cPlayer::getKeyCount() {
    return keys;
}

ObjectType cPlayer::getEquippedObjectA() {
    return ObjectType::Sword;
}

ObjectType cPlayer::getEquippedObjectB() {
    return ObjectType::NoObject;
}

//int cPlayer::GetEquippedObjectA() {

//}
void cPlayer::SetScene(int sceneX, int sceneY) {
    this->sceneX = sceneX;
    this->sceneY = sceneY;
}

void cPlayer::SetLevel(int level) {
    this->level = level;
}

int cPlayer::GetMoney() const {
    return money;
}

void cPlayer::SetMoney(int amount) {
    money = amount;
}

void cPlayer::InDungeonDoor() {
    // Reset protection
    isProtected = false;
    if (overworld) {
        transition = Direction::Below;
    } else {
        transition = Direction::Above;
    }
    overworld = !overworld;
    SetDirection(Direction::Down);
}
