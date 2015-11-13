#include "cGame.h"
#include "Globals.h"
#include "cBeam.h"
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

cGame::cGame(void) : sceneOffsetx(0), sceneOffsety(0), sceneX(0), sceneY(0)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
    bool res=true;

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
    objects.push_back(std::unique_ptr<cKey>(
        new cKey(GAME_WIDTH+200,64,width,height)));

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
    LoadLevel(2);
    
    currentScreen = Screens::Home;
    //currentScreen = Screens::Credits;
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
        default:
            break;
    }
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

                if (oldDir != Player.GetDirection()) {
                    Player.SetAnimation(to_string(Player.GetDirection()));
                }
                if (keys['a']) {
                    if (!Player.IsAttacking()) {
                        Player.Attack();
                        if (Player.GetHitpoints() == Player.GetMaxHitpoints()) {
                            cRect swordArea = Player.GetSwordArea();
                            std::unique_ptr<cBicho> beam(
                                new cBeam(swordArea.left, swordArea.bottom, sceneX,
                                          sceneY, Player.GetDirection()));
                            beam->SetAnimation(to_string(Player.GetDirection()));

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
                }
            }
            for (auto it = objects.begin(); it != objects.end(); ) {
                if ((*it)->Collides(pRect)) {
                    Player.PickUp();
                    Gui.setKeyCount(Player.getKeyCount());
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
                    it = enemies.erase(it);
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
    }
    else if (currentScreen == Screens::GameOver && counter < 32000) {
        ++counter;
    }
    return res;


}

void cGame::startTransition() {
    transitionState = Player.GetTransition();
    // Remove all enemies.
    enemies.clear();
    state = STATE_SCREEN_CHANGE;
    frame = 0;
}

void cGame::endTransition() {
    state = STATE_STATIC_CAMERA;
    if (transitionState == Direction::Above) {
        LoadLevel(2);
    }
    if (transitionState == Direction::Below) {
        LoadLevel(3);
    }
    UpdateScenePos(transitionState);
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

void cGame::PopulateEnemies() {
    const cMap &map = Scene.GetMap();
    int xo = sceneX * VIEW_WIDTH;
    int yo = sceneY * VIEW_HEIGHT;
    // Arbitrary value.
    
    std::vector<std::pair<int,int>> freeCells;
    for (int x = xo; x < xo + VIEW_WIDTH; ++x) {
        for (int y = yo; y < yo + VIEW_HEIGHT; ++y) {
            if (!map.Obstacle(x, y)) {
                freeCells.push_back({x, y});
            }
        }
    }
    int numEnemies = freeCells.size() / 20;
    while (numEnemies--) {
        int i = rand() % freeCells.size();
        int x = freeCells[i].first;
        int y = freeCells[i].second;
        if (rand()&1) {
            enemies.push_back(std::unique_ptr<cBicho>(
                new cOctorok(x * TILE_SIZE, y * TILE_SIZE, sceneX, sceneY)));
        } else {
            enemies.push_back(std::unique_ptr<cBicho>(
                new cWorm(x * TILE_SIZE, y * TILE_SIZE, sceneX, sceneY, Player)));
        }
        std::swap(freeCells[i], freeCells[freeCells.size()-1]);
        freeCells.pop_back();
    }
}
