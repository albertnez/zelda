#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cOctorok.h"
#include "cData.h"
#include "utils.h"
#include "cGUI.h"
#include "cObject.h"
#include "cKey.h"
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
    Credits,
    GameOver
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
    void DrawGameScreen(bool drawEnemies);
    void CalculateTransition();
    

private:
    void Restart();
    void PopulateEnemies();
    std::unique_ptr<cBicho> GenerateRandomEnemy(int x, int y, int sceneX, int sceneY);
    void SpawnRandomObject(int x, int y);
    Direction NextGameOverRotation(Direction dir);

    static const int enemySpawnBoundary;
    static const int spawnObjectProb;

    bool keys[256];
    cScene Scene;
    cPlayer Player;
    std::list<std::unique_ptr<cBicho>> enemies;
    std::list<std::unique_ptr<cObject>> objects;
    std::list<std::unique_ptr<cBicho>> allies;
    cData Data;
    int sceneOffsetx = 0;
    int sceneOffsety = 0;
    int sceneX;
    int sceneY;
    int level;
    Direction transitionState;
    int state;
    int frame = 0;
    cGUI Gui;
    int currentScreen;
    int counter = 0;
    bool triggerKeyReleased = true;
};
