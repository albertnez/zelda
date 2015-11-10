#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cOctorok.h"
#include "cData.h"
#include "utils.h"
#include "cGUI.h"
#include <algorithm>
#include <list>
#include <memory>

extern const int GAME_WIDTH;
extern const int GAME_HEIGHT;

extern const int STATE_STATIC_CAMERA;
extern const int STATE_SCREEN_CHANGE;
extern const int STATE_SCENE_CHANGE;

enum Screens : int {
    Home = 0,
    GameScreen,
    Instructions,
    Credits
};

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
    void LoadLevel(int level);
    //Output
    void Render();
    void setState(int s);
    void UpdateScenePos(Direction dir);
 
private:
    bool keys[256];
    cScene Scene;
    cPlayer Player;
    std::list<std::unique_ptr<cBicho>> enemies;
    cData Data;
    int sceneOffsetx = 0;
    int sceneOffsety = 0;
    int sceneX;
    int sceneY;
    Direction transitionState;
    int state;
    int frame = 0;
    cGUI Gui;
    int currentScreen;
};
