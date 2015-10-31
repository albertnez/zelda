#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "utils.h"
#include <vector>

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKDOWN	0
#define STATE_LOOKLEFT	1
#define STATE_LOOKUP    2
#define STATE_LOOKRIGHT 3
#define STATE_WALKDOWN  4
#define STATE_WALKLEFT  5
#define STATE_WALKUP    6
#define STATE_WALKRIGHT 7
#define STATE_TRANSITIONUP		8
#define STATE_TRANSITIONDOWN	9
#define STATE_TRANSITIONLEFT	10
#define STATE_TRANSITIONRIGHT	11
#define STATE_TRANSITIONABOVE   12
#define STATE_TRANSITIONBELOW	13


class cBicho
{
public:
	typedef std::vector<std::vector<int>> Map;
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
	void Damage(int hp);
	void SetAttack(int attack);
	int GetAttack();
	bool IsDead();

	bool Collides(cRect *rc);
	// Checks collision with tiles
	bool CollidesMap(const Map &map);
	bool CollidesMapWall(const Map &map,bool right);
	bool CollidesMapFloor(const Map &map);
	// Returns whether reaches the limit of the map.
	bool ReachesMapLimit(const Map &map, int scene_x, int scene_y);
	// Called when cBicho reaches limit of map.
	virtual void ReachLimit(Direction dir);


	void GetArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	
	void MoveLeft(const Map &map, int scene_x = 0, int scene_y = 0);
	void MoveUp(const Map &map, int scene_x = 0, int scene_y = 0);
	void MoveRight(const Map &map, int scene_x = 0, int scene_y = 0);
	void MoveDown(const Map &map, int scene_x = 0, int scene_y = 0);   
	void Jump(const Map &map);
	void Stop();
	void Logic(const Map &map);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();
	
protected:
	int x,y;
private:
	int w,h;
	int state;
	int hitpoints;
	int max_hitpoints;
	int attack;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq,delay;
};
