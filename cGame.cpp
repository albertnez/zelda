#include "cGame.h"
#include "Globals.h"
#include <iostream>


cGame::cGame(void)
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

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"blocks.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"bub.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(32,32);
	Player.SetTile(4,1);
	Player.SetWidthHeight(32,32);
	Player.SetState(STATE_LOOKRIGHT);

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


//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if (keys[27]) {
		res = false;
	}

	if (state == STATE_STATIC_CAMERA) {
		bool move_vert = keys[GLUT_KEY_DOWN] ^ keys[GLUT_KEY_UP];
		if (move_vert) {
			if (keys[GLUT_KEY_DOWN]) {
				Player.MoveDown(Scene.GetMap());
			}
			else if (keys[GLUT_KEY_UP]) {
				Player.MoveUp(Scene.GetMap());
			}
		}
		bool move_hor = keys[GLUT_KEY_LEFT] ^ keys[GLUT_KEY_RIGHT];
		if (move_hor) {
			if (keys[GLUT_KEY_LEFT]) {
				Player.MoveLeft(Scene.GetMap());
			}
			else if (keys[GLUT_KEY_RIGHT]) {
				Player.MoveRight(Scene.GetMap());
			}
		}
		if (!(move_vert || move_hor)) {
			Player.Stop();
		}


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
	Player.EndTransition();
}

//Output
void cGame::Render()
{


	if (state == STATE_SCREEN_CHANGE) {
		if (transitionState == Direction::Right) {
			sceneOffsetx += X_TRANSITION;
		}
		else if (transitionState == Direction::Left) {
			sceneOffsetx -= X_TRANSITION;
		}
		else if (transitionState == Direction::Down) {
			sceneOffsety -= Y_TRANSITION;
		}
		else if (transitionState == Direction::Up) {
			sceneOffsetx += Y_TRANSITION;
		}

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		

		glOrtho(
			sceneOffsetx, sceneOffsetx+GAME_WIDTH,
			sceneOffsety, sceneOffsety+GAME_HEIGHT, 0, 1
			);
		glMatrixMode(GL_MODELVIEW);
		frame++;
		if (frame == TRANSITION_FRAMES) {
			endTransition();
		}
	}

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	Scene.Draw(Data.GetID(IMG_BLOCKS));
	Player.Draw(Data.GetID(IMG_PLAYER));

	glutSwapBuffers();
}
