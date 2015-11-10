#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "utils.h"
#include "cMap.h"
#include "cAnim.h"
#include <unordered_map>

extern const int FRAME_DELAY;
extern const int STEP_LENGTH;

class cBicho
{
public:
	enum State {
		Look = 0,
		Walk,
	};
	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x, int *y);
	void SetTile(int tx,int ty);
	void GetTile(int *tx, int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w, int *h);
	void SetHitpoints(int hp);
	int GetHitpoints();
	void SetMaxHitpoints(int hp);
	int GetMaxHitpoints();
	void Heal(int hp);
	bool Damage(int hp);
	void SetAttack(int attack);
	int GetAttack();
	bool IsDead();

	bool Collides(const cRect &rect);
	// Checks collision with tiles
	bool CollidesMap(const cMap &map);
	// Returns whether reaches the limit of the map.
	bool ReachesMapLimit(const cMap &map, int scene_x, int scene_y);
	// Called when cBicho reaches limit of map. Returns true if
	// it can go through the limit (like link going to next view).
	virtual bool ReachLimit(Direction dir);
	// Reset Animation.
	void ResetAnimation();
	virtual void SetAnimation(const std::string& name);
	std::string GetAnimation();


    void GetArea(cRect &rc);
    void Draw(int texId, int texWidth, int texHeight);
    virtual void SpecificDraw(int texId, int texWidth, int texHeight);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	
	// Returns True if it can move, false otherwise.
	bool Move(const cMap &map, Direction dir, int sceneX = 0, int sceneY = 0);
	void Stop();
	void Logic(const cMap &map);
    virtual void SpecificLogic(const cMap &map);

	Direction GetDirection();
	void SetDirection(Direction dir);
	State GetState();
	void SetState(State state);

    void NextFrame(int max);
	
protected:
        void UpdateProtected();

    int x,y;
    int w,h;
    int stepLength;
    State state;
    Direction direction;
    int hitpoints;
    int max_hitpoints;
    int attack;
    bool isProtected;
    int protectionTime;
    int maxProtectionTime;

	std::string currentAnimation;
	std::unordered_map<std::string, cAnim> animations;
};
