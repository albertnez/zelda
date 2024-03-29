#include "Globals.h"
#include "cBat.h"
#include "cBeam.h"
#include "cBoss.h"
#include "cGame.h"
#include "cHeart.h"
#include "cPlusHeart.h"
#include "cRupee.h"
#include "cStar.h"
#include "cWorm.h"
#include <iostream>

const int GAME_WIDTH = 256;
const int GAME_HEIGHT = 224;

// TRANSITION_SPEED should divide Game width and game height!
const int TRANSITION_SPEED = 4;
const int X_TRANSITION_FRAMES = TRANSITION_SPEED * VIEW_WIDTH;
const int Y_TRANSITION_FRAMES = TRANSITION_SPEED * VIEW_HEIGHT;

const int STATE_STATIC_CAMERA = 0;
const int STATE_SCREEN_CHANGE = 1;
const int STATE_SCENE_CHANGE = 2;

const int KEY_PRESS_WAIT_FRAMES = 5;

const int cGame::enemySpawnBoundary = 3;
const int cGame::spawnObjectProb = 80;  // Probability out of 100

cGame::cGame(void) : sceneOffsetx(0), sceneOffsety(0), sceneX(0), sceneY(0)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
    bool res=true;

    for (int i = 0; i < 256; ++i) {
        keys[i] = false;
    }
    triggerKeyReleased = true;
    sceneX = 0;
    sceneY = 0;
    Gui = cGUI();
    Player = cPlayer();
    Player.DeactivateStar();
    sceneOffsetx = 0;
    sceneOffsety = 0;

    state = STATE_STATIC_CAMERA;

    //Graphics initialization
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
    glMatrixMode(GL_MODELVIEW);
    
    glAlphaFunc(GL_GREATER, 0.05f);
    glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Load textures
    if (!Data.LoadImage(Images::Tileset, "res/tiles.png", GL_RGBA)) {
        throw std::runtime_error("Error loading res/tileset.png");
    }
    if (!Data.LoadImage(Images::Sprites, "res/sprites.png", GL_RGBA)) {
        throw std::runtime_error("Error loading res/sprites.png");
    }
    if (!Data.LoadImage(Images::Enemies, "res/enemies.png", GL_RGBA)) {
        throw std::runtime_error("Error loading res/enemies.png");
    }
    if (!Data.LoadImage(Images::Objects, "res/objects.png", GL_RGBA)) {
        throw std::runtime_error("Error loading res/objects.png");
    }
    //Scene initialization

    //res = Scene.LoadLevel(2);
    //if(!res) return false;

    //Player initialization
    Player.SetWidthHeight(32,32);
    Player.SetTile(5, 5);
    Player.SetWidthHeight(16,16);
    Player.SetDirection(Direction::Down);
    Player.SetState(cBicho::State::Look);
    Player.SetHitpoints(6);
    Player.SetMaxHitpoints(6);

    //enemies.push_back(std::unique_ptr<cOctorok>(new cOctorok(0, 0, 0, 0)));
    //enemies.back()->SetTile(7, 7);

    int width, height;
    Data.GetSize(Images::Objects, &width, &height);
    objects.push_back(
        std::unique_ptr<cObject>(new cKey(30 * TILE_SIZE, 3 * TILE_SIZE)));
    objects.push_back(
        std::unique_ptr<cObject>(new cPlusHeart(28 * TILE_SIZE, 7 * TILE_SIZE)));

    res = Data.LoadImage(Images::Hearts, "res/life.png", GL_RGBA);
    if (!res) return false;

    res = Data.LoadImage(Images::Font, "res/nesfont_w.png", GL_RGBA);
    if (!res) return false;
    res = Data.LoadImage(Images::Interface, "res/interface.png", GL_RGBA);
    if (!res) return false;
    res = Data.LoadImage(Images::Title, "res/zeldatitle.png", GL_RGBA);
    if (!res) return false;
    Gui.init();
    Gui.setMaxHP(Player.GetMaxHitpoints());
    Gui.setHP(Player.GetHitpoints());
    Gui.setKeyCount(Player.getKeyCount());
    Gui.setEquippedObjectA(Player.getEquippedObjectA());
    Gui.setEquippedObjectB(Player.getEquippedObjectB());
    level = 2;
    LoadLevel(level);
    
    currentScreen = Screens::Home;
    return res;

}

bool cGame::Loop()
{
    bool res=true;

    res = Process();
    if(res) Render();

    return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
    keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

void cGame::setState(int s) {
    state = s;
}

void cGame::UpdateScenePos(Direction dir) {
    switch (dir) {
        case Direction::Up:
            ++sceneY;
            break;
        case Direction::Down:
            --sceneY;
            break;
        case Direction::Left:
            --sceneX;
            break;
        case Direction::Right:
            ++sceneX;
            break;
        case Direction::Below:
            sceneX = 0;
            sceneY = 0;
            break;
        case Direction::Above:
            sceneX = 1;
            sceneY = 1;
            break;
        default:
            break;
    }
    sceneOffsetx = sceneX * VIEW_WIDTH * TILE_SIZE;
    sceneOffsety = sceneY * VIEW_HEIGHT * TILE_SIZE;
}

//Process
bool cGame::Process()
{
    bool res=true;
    
    //Process Input
    if (keys[27]) {
        res = false;
    }

    if (currentScreen == Screens::GameScreen) {
        if (Player.GetHitpoints() == 0) {
            currentScreen = Screens::GameOver;
            counter = 0;
        }
        if (!triggerKeyReleased) {
            if(!keys['h'])triggerKeyReleased = true;
        }
        else if (keys['h']) {
            currentScreen = Screens::Instructions;
            triggerKeyReleased = false;
        }
        if (state == STATE_STATIC_CAMERA) {
            if (!Player.IsAttacking()) {
                Direction oldDir = Player.GetDirection();
                Direction dir = Direction::None;
                if (keys[GLUT_KEY_UP]) dir = Direction::Up;
                else if (keys[GLUT_KEY_DOWN]) dir = Direction::Down;
                else if (keys[GLUT_KEY_LEFT]) dir = Direction::Left;
                else if (keys[GLUT_KEY_RIGHT]) dir = Direction::Right;

                if (dir == Direction::None) Player.Stop();
                else Player.Move(Scene.GetMap(), dir, sceneX, sceneY);

                int tx, ty;
                if (
                    Player.CollidesDoor(Scene.GetMap(),tx, ty)&&Player.getKeyCount()>=1) {
                    Scene.OpenDoor(tx, ty);
                    Player.UseKey();
                    Gui.setKeyCount(Player.getKeyCount());
                }


                if (oldDir != Player.GetDirection()) {
                    Player.SetAnimation(to_string(Player.GetDirection()));
                }
                if (keys['a']) {
                    if (!Player.IsAttacking()) {
                        Player.Attack();
                        if (Player.GetHitpoints() == Player.GetMaxHitpoints()) {
                            cRect swordArea = Player.GetSwordArea();
                            int x, y;
                            Player.GetPosition(&x, &y);
                            std::unique_ptr<cBicho> beam(
                                new cBeam(swordArea.left, swordArea.bottom, sceneX,
                                          sceneY, Player.GetDirection()));

                            allies.push_back(std::move(beam));
                        }
                    }
                }
            }
            for (auto &ally : allies) {
                ally->Logic(Scene.GetMap());
            }
            for (auto &enemy : enemies) {
                enemy->Logic(Scene.GetMap());
            }
            cRect pRect = Player.GetArea();
            cRect swordRect = Player.GetSwordArea();
            //Game Logic
            for (auto &enemy : enemies) {
                // Sword beams.
                for (auto &ally : allies) {
                    if (!ally->IsDead() && enemy->Collides(ally->GetArea())) {
                        enemy->Damage(ally->GetAttack());
                    }
                }
                if (Player.IsAttacking() && enemy->Collides(swordRect)) {
                    enemy->Damage(Player.GetAttack());
                }
                if (enemy->Collides(pRect)) {
                    Player.Damage(enemy->GetAttack());
                    // If it has star, let player hit them!
                    if (Player.HasStar()) {
                        enemy->Damage(Player.GetAttack());
                    }
                }
            }
            for (auto it = objects.begin(); it != objects.end(); ) {
                if ((*it)->Collides(pRect)) {
                    (*it)->Apply(Player);
                    // Update GUI
                    Gui.setKeyCount(Player.getKeyCount());
                    Gui.SetMoney(Player.GetMoney());
                    Gui.setMaxHP(Player.GetMaxHitpoints());
                    Gui.setHP(Player.GetHitpoints());

                    it = objects.erase(it);
                }
                else {
                    ++it;
                }
            }
            Player.Logic(Scene.GetMap());

            // Remove dead enemies:
            for (auto it = enemies.begin(); it != enemies.end(); ) {
                if ((*it)->IsDead()) {
                    // With some probability, spawn a heart.
                    if ((*it)->SpawnObjects()) {
                        if ((rand()%100) < spawnObjectProb) {
                            int x, y;
                            (*it)->GetPosition(&x, &y);
                            SpawnRandomObject(x, y);
                        }
                    }
                    it = enemies.erase(it);
                    if (enemies.empty() && level == 3) {
                        if (sceneX == 0 && sceneY == 0) {
                            objects.push_back(std::unique_ptr<cObject>(
                                new cKey(8 * TILE_SIZE, 5 * TILE_SIZE)));
                        } else if (sceneX == 1 && sceneY == 1) {
                            objects.push_back(std::unique_ptr<cObject>(
                                new cKey(29 * TILE_SIZE, 19 * TILE_SIZE)));
                        } else if (sceneX == 0 && sceneY == 1) {
                            // END OF THE GAME
                            currentScreen = Screens::Credits;
                        }
                    }

                } else {
                    ++it;
                }
            }
            for (auto it = allies.begin(); it != allies.end(); ) {
                if ((*it)->IsDead()) {
                    it = allies.erase(it);
                } else {
                    ++it;
                }
            }

            if (Player.IsChangingScreen()) {
                startTransition();
            }
        }
        else if (state == STATE_SCREEN_CHANGE) {
            CalculateTransition();
        }

        
    }
    else if (currentScreen == Screens::Home) {
        if (keys[13])currentScreen = Screens::GameScreen;
    }
    else if (currentScreen == Screens::Instructions) {
        if (!triggerKeyReleased) {
            if (!keys['h'])triggerKeyReleased = true;
        }
        else if (keys['h']) {
            currentScreen = Screens::GameScreen;
            triggerKeyReleased = false;
        }   
    }
    else if (currentScreen == Screens::Credits && counter < 32000) {
        ++counter;
        if (keys[13]) {
            Restart();
        }
    }
    else if (currentScreen == Screens::GameOver && counter < 32000) {
        ++counter;
        if (counter >= 160 && keys[13]) {
            Restart();
        }
    }
    return res;


}

void cGame::startTransition() {
    transitionState = Player.GetTransition();
    // Remove all enemies.
    enemies.clear();
    // Remove objects that are not keys:
    objects.remove_if([](const std::unique_ptr<cObject> &o) -> bool {
        return o->GetType() != ObjectType::Key &&
               o->GetType() != ObjectType::PlusHeart;
    });

    state = STATE_SCREEN_CHANGE;
    frame = 0;
}

void cGame::endTransition() {
    state = STATE_STATIC_CAMERA;
    if (transitionState == Direction::Above) {
        level = 2;
        LoadLevel(level);
        Player.SetLevel(level);
        Player.SetTile(8 + VIEW_WIDTH, 8 + VIEW_HEIGHT);
    }
    if (transitionState == Direction::Below) {
        //Remove objects.
        objects.clear();

        int width, height;
        Data.GetSize(Images::Objects, &width, &height);
        LoadLevel(3);
        Player.SetLevel(3);
        level = 3;
        LoadLevel(level);
        Player.SetLevel(level);
        Player.SetPosition(7.5f * TILE_SIZE, 1 * TILE_SIZE);
    }
    UpdateScenePos(transitionState);
    Player.SetScene(sceneX, sceneY);
    PopulateEnemies();
    Player.EndTransition();
    Gui.setViewX(sceneOffsetx / (VIEW_WIDTH*TILE_SIZE));
    Gui.setViewY(sceneOffsety / (VIEW_HEIGHT*TILE_SIZE));
}

void cGame::LoadLevel(int level) {
    if (!Scene.LoadLevel(level)) {
        throw std::runtime_error("Error loading res/tileset.png");
    }
    cMap m = Scene.GetMap();
    Gui.setMaxViewsX(m.Width() / VIEW_WIDTH);
    Gui.setMaxViewsY(m.Height() / VIEW_HEIGHT);
    Gui.setLevel(level);
}

//Output
void cGame::Render()
{
    if (currentScreen == Screens::Home) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(
            0, GAME_WIDTH,
            0, GAME_HEIGHT, 0, 1
            );
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        Gui.DrawTitle(Data.GetID(Images::Title), GAME_WIDTH, GAME_HEIGHT);
    }
    else if (currentScreen == Screens::GameOver) {
        if ((counter % 10) == 0) {
            Player.SetDirection(NextGameOverRotation(Player.GetDirection()));
            Player.SetAnimation(to_string(Player.GetDirection()));
        }
        
        if (counter <= 20) {
            DrawGameScreen(false);
        }
        else if (counter <= 120) {
            glColor3f(1.0f, 0.0f, 0.0f);
            DrawGameScreen(false);
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        else if (counter <= 140) {
            glColor3f(0.67f, 0.0f, 0.0f);
            DrawGameScreen(false);
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        else if (counter <= 160) {
            glColor3f(0.33f, 0.0f, 0.0f);
            DrawGameScreen(false);
            glColor3f(1.0f, 1.0f, 1.0f);
        }
        else {
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(
                sceneOffsetx, sceneOffsetx + GAME_WIDTH,
                sceneOffsety, sceneOffsety + GAME_HEIGHT, 0, 1
                );
            glClear(GL_COLOR_BUFFER_BIT);
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            Gui.Draw(Data.GetID(Images::Hearts), Data.GetID(Images::Font),
                Data.GetID(Images::Interface), GAME_WIDTH, GAME_HEIGHT);
            Gui.DrawGameOver(Data.GetID(Images::Font), GAME_WIDTH, GAME_HEIGHT);
        }
        
        
    }
    else if (currentScreen == Screens::Instructions) {
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(
            0, GAME_WIDTH,
            0, GAME_HEIGHT, 0, 1
            );
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        Gui.Draw(Data.GetID(Images::Hearts), Data.GetID(Images::Font),
            Data.GetID(Images::Interface), GAME_WIDTH, GAME_HEIGHT);
        Gui.DrawInstructions(Data.GetID(Images::Font), GAME_WIDTH, GAME_HEIGHT);

    }

    else if (currentScreen == Screens::Credits) {
        // Clear Gui Xo and Yo for text.
        Gui.setXo(0);
        Gui.setYo(0);
        int yo = -counter/2;
        int yf = GAME_HEIGHT - counter / 2;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(
            0, GAME_WIDTH,
            yo, yf, 0, 1
            );
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        Gui.DrawCredits(Data.GetID(Images::Font), Data.GetID(Images::Interface),
            GAME_WIDTH, GAME_HEIGHT);
    }
    else if (currentScreen == Screens::GameScreen) {
        
        DrawGameScreen(true);
        
        
    }
    glutSwapBuffers();
}


void cGame::CalculateTransition() {
    int px, py, pw, ph;
    Player.GetPosition(&px, &py);
    Player.GetWidthHeight(&pw, &ph);

    if (transitionState == Direction::Right) {
        sceneOffsetx += TRANSITION_SPEED;
        px = std::max(px, sceneOffsetx);
    }
    else if (transitionState == Direction::Left) {
        sceneOffsetx -= TRANSITION_SPEED;
        px = std::min(px, sceneOffsetx + GAME_WIDTH - pw);
    }
    else if (transitionState == Direction::Down) {
        sceneOffsety -= TRANSITION_SPEED;
        py = std::min(py, sceneOffsety + VIEW_HEIGHT * TILE_SIZE - ph);
    }
    else if (transitionState == Direction::Up) {
        sceneOffsety += TRANSITION_SPEED;
        py = std::max(py, sceneOffsety);
    }
    Player.SetPosition(px, py);

        
    frame++;
    int targetFrames = X_TRANSITION_FRAMES;
    if (transitionState == Direction::Up || transitionState == Direction::Down) {
        targetFrames = Y_TRANSITION_FRAMES;
    }
    if (frame == targetFrames) {
        endTransition();
    }
}


void cGame::DrawGameScreen(bool drawEnemies) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(
        sceneOffsetx, sceneOffsetx + GAME_WIDTH,
        sceneOffsety, sceneOffsety + GAME_HEIGHT, 0, 1
        );
    glMatrixMode(GL_MODELVIEW);
    Gui.setHP(Player.GetHitpoints());
    Gui.setXo(sceneOffsetx);
    Gui.setYo(sceneOffsety);
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();

    int width, height;
    Scene.Draw(Data.GetID(Images::Tileset));
    // Draw enemies.
    if (drawEnemies) {
        
        for (const auto &object : objects) {
            object->Draw(Data.GetID(Images::Objects));
        }
        Data.GetSize(Images::Sprites, &width, &height);
        for (const auto &enemy : enemies) {
            enemy->Draw(Data.GetID(Images::Sprites), width, height);
        }
    }
    // Draw Sword Beam
    if (drawEnemies) {
        Data.GetSize(Images::Sprites, &width, &height);
        for (const auto &ally : allies) {
            ally->Draw(Data.GetID(Images::Sprites), width, height);
        }

        
    }
    // Draw player.
    Data.GetSize(Images::Sprites, &width, &height);
    Player.Draw(Data.GetID(Images::Sprites), width, height);

    Gui.Draw(Data.GetID(Images::Hearts), Data.GetID(Images::Font),
             Data.GetID(Images::Interface), GAME_WIDTH, GAME_HEIGHT);
}

void cGame::Restart() {
    counter = 0;
    frame = 0;
    objects.clear();
    enemies.clear();
    allies.clear();
    Init();

}

void cGame::PopulateEnemies() {
    const cMap &map = Scene.GetMap();
    int xo = sceneX * VIEW_WIDTH;
    int yo = sceneY * VIEW_HEIGHT;

    if (level == 3 && sceneX == 0 && sceneY == 1) {
        enemies.push_back(std::unique_ptr<cBicho>(new cBoss(
            4 * TILE_SIZE, 15 * TILE_SIZE, sceneX, sceneY, enemies)));
        return;
    }
    
    std::vector<std::pair<int,int>> freeCells;
    for (int x = xo + enemySpawnBoundary; x < xo + VIEW_WIDTH - enemySpawnBoundary; ++x) {
        for (int y = yo + enemySpawnBoundary; y < yo + VIEW_HEIGHT - enemySpawnBoundary; ++y) {
            if (!map.Obstacle(x, y)) {
                freeCells.push_back({x, y});
            }
        }
    }
    int numEnemies = freeCells.size() / 12;
    while (numEnemies--) {
        int i = rand() % freeCells.size();
        int x = freeCells[i].first;
        int y = freeCells[i].second;
        enemies.push_back(GenerateRandomEnemy(x * TILE_SIZE, y * TILE_SIZE, sceneX, sceneY));
        std::swap(freeCells[i], freeCells[freeCells.size()-1]);
        freeCells.pop_back();
    }
}

std::unique_ptr<cBicho> cGame::GenerateRandomEnemy(int x, int y, int sceneX, int sceneY) {
    switch (rand()%3) {
        case 0:
            return std::unique_ptr<cBicho>(new cOctorok(x, y, sceneX, sceneY));
            break;
        case 1:
            return std::unique_ptr<cBicho>(new cWorm(x, y, sceneX, sceneY, Player));
            break;
        case 2:
        default:
            return std::unique_ptr<cBicho>(new cBat(x, y, sceneX, sceneY));
            break;
    }
}

void cGame::SpawnRandomObject(int x, int y) {
    int width, height;
    Data.GetSize(Images::Objects, &width, &height);
    switch (rand()%3) {
        case 0:
            objects.push_back(std::unique_ptr<cObject>(new cHeart(x, y)));
            break;
        case 1:
            objects.push_back(std::unique_ptr<cObject>(new cRupee(x, y)));
            break;
        case 2:
        default:
            objects.push_back(std::unique_ptr<cObject>(new cStar(x, y)));
            break;
    }
}

Direction cGame::NextGameOverRotation(Direction dir) {
    switch (dir) {
        case Direction::Up:
            return Direction::Right;
            break;
        case Direction::Right:
            return Direction::Down;
            break;
        case Direction::Down:
            return Direction::Left;
            break;
        default:
            return Direction::Up;
            break;
    }
}
