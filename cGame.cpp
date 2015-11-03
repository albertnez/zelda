#include "cGame.h"
#include "Globals.h"
#include <iostream>

const int GAME_WIDTH = 256;
const int GAME_HEIGHT = 176;

// TRANSITION_SPEED should divide Game width and game height!
const int TRANSITION_SPEED = 4;
const int X_TRANSITION_FRAMES = TRANSITION_SPEED * VIEW_WIDTH;
const int Y_TRANSITION_FRAMES = TRANSITION_SPEED * VIEW_HEIGHT;

const int STATE_STATIC_CAMERA = 0;
const int STATE_SCREEN_CHANGE = 1;
const int STATE_SCENE_CHANGE = 2;

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

	// Load textures
	if (!Data.LoadImage(Images::Tileset, "res/tileset.png", GL_RGBA)) {
		throw std::runtime_error("Error loading res/tileset.png");
	}
	if (!Data.LoadImage(Images::Sprites, "res/sprites.png", GL_RGBA)) {
		throw std::runtime_error("Error loading res/sprites.png");
	}
	
	//Scene initialization
	res = Data.LoadImage(Images::Blocks, "blocks.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(2);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(Images::Player, "bub.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(32,32);
	Player.SetTile(5, 5);
	Player.SetWidthHeight(16,16);
	Player.SetDirection(Direction::Right);
	Player.SetState(cBicho::State::Look);

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

	if (state == STATE_STATIC_CAMERA) {
		Direction dir = Direction::None;
		if (keys[GLUT_KEY_UP]) dir = Direction::Up;
		else if (keys[GLUT_KEY_DOWN]) dir = Direction::Down;
		else if (keys[GLUT_KEY_LEFT]) dir = Direction::Left;
		else if (keys[GLUT_KEY_RIGHT]) dir = Direction::Right;

		if (dir == Direction::None) Player.Stop();
		else Player.Move(Scene.GetMap(), dir, sceneX, sceneY);

		//Game Logic
		Player.Logic(Scene.GetMap());

		if (Player.IsChangingScreen()) {
			startTransition();
		}
	}

	return res;
}

void cGame::startTransition() {
	transitionState = Player.GetTransition();
	state = STATE_SCREEN_CHANGE;
	frame = 0;
}

void cGame::endTransition() {
	state = STATE_STATIC_CAMERA;
	UpdateScenePos(transitionState);
	Player.EndTransition();
}

//Output
void cGame::Render()
{

	if (state == STATE_SCREEN_CHANGE) {
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
			py = std::min(py, sceneOffsety + GAME_HEIGHT - ph);
		}
		else if (transitionState == Direction::Up) {
			sceneOffsety += TRANSITION_SPEED;
			py = std::max(py, sceneOffsety);
		}
		Player.SetPosition(px, py);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		

		glOrtho(
			sceneOffsetx, sceneOffsetx+GAME_WIDTH,
			sceneOffsety, sceneOffsety+GAME_HEIGHT, 0, 1
			);
		glMatrixMode(GL_MODELVIEW);
		frame++;
		int targetFrames = X_TRANSITION_FRAMES;
		if (transitionState == Direction::Up || transitionState == Direction::Down) {
			targetFrames = Y_TRANSITION_FRAMES;
		}
		if (frame == targetFrames) {
			endTransition();
		}
	}

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	int width, height;
	Scene.Draw(Data.GetID(Images::Tileset));
	Data.GetSize(Images::Sprites, &width, &height);
	Player.Draw(Data.GetID(Images::Sprites), width, height);

	glutSwapBuffers();
}
