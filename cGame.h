#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cData.h"
#include "utils.h"

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;
extern const int TRANSITION_FRAMES;
extern const int X_TRANSITION;
extern const int Y_TRANSITION;

extern const int STATE_STATIC_CAMERA;
extern const int STATE_SCREEN_CHANGE;
extern const int STATE_SCENE_CHANGE;

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
	void UpdateScenePos(Direction dir);
 
private:
	bool keys[256];
	cScene Scene;
	cPlayer Player;
	cData Data;
	int sceneOffsetx = 0;
	int sceneOffsety = 0;
	int sceneX;
	int sceneY;
	Direction transitionState;
	int state;
	int frame = 0;
};
