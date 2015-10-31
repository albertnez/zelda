#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "utils.h"
#include <vector>

extern const int FRAME_DELAY;
extern const int STEP_LENGTH;

class cBicho
{
public:
	enum State {
		Look = 0,
		Walk,
	};
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
	
	void Move(const Map &map, Direction dir, int sceneX = 0, int sceneY = 0);
	void Stop();
	void Logic(const Map &map);

	Direction GetDirection();
	void SetDirection(Direction dir);
	State GetState();
	void SetState(State state);

	void NextFrame(int max);
	int  GetFrame();
	
protected:
	int x,y;
private:
	int w,h;
	Direction direction;
	State state;
	int hitpoints;
	int max_hitpoints;
	int attack;

	int seq,delay;
};
