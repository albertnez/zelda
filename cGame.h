#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"

#define GAME_WIDTH	640
#define GAME_HEIGHT 480
#define TRANSITION_FRAMES 60
#define X_TRANSITION 8
#define Y_TRANSITION 6

#define STATE_STATIC_CAMERA 0
#define STATE_SCREEN_CHANGE 1
#define STATE_SCENE_CHANGE 2



class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	void startTransition();
	void endTransition();
	//Output
	void Render();
	void setState(int s);
 
private:
	bool keys[256];
	cScene Scene;
	cPlayer Player;
	cData Data;
	int sceneOffsetx = 0;
	int sceneOffsety = 0;
	int transitionState;
	int state;
	int frame = 0;
};
