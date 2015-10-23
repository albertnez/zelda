#pragma once

#include "cTexture.h"
#include "Globals.h"

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

class cRect
{
public:
	int left,top,
		right,bottom;
};

class cBicho
{
public:
	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x,int *y);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w,int *h);

	bool Collides(cRect *rc);
    // Checks collision with tiles
    bool CollidesMap(int *map);
	bool CollidesMapWall(int *map,bool right);
	bool CollidesMapFloor(int *map);
	void GetArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	
    void MoveLeft(int *map);
    void MoveUp(int *map);
	void MoveRight(int *map);
    void MoveDown(int *map);   

	void Jump(int *map);
	void Stop();
	void Logic(int *map);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();
	
private:
	int x,y;
	int w,h;
	int state;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq,delay;
};
