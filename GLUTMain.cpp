#include "Globals.h"
#include "cGame.h"

#include <chrono>
#include <thread>

#ifdef _WIN32
#include <Windows.h>

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif

cGame Game;

void AppRender()
{
    Game.Render();
}
void AppKeyboard(unsigned char key, int x, int y)
{
    Game.ReadKeyboard(key,x,y,true);
}
void AppKeyboardUp(unsigned char key, int x, int y)
{
    Game.ReadKeyboard(key,x,y,false);
}
void AppSpecialKeys(int key, int x, int y)
{
    Game.ReadKeyboard(key,x,y,true);
}
void AppSpecialKeysUp(int key, int x, int y)
{
    Game.ReadKeyboard(key,x,y,false);
}
void AppMouse(int button, int state, int x, int y)
{
    Game.ReadMouse(button,state,x,y);
}
void AppIdle()
{
    int st = glutGet(GLUT_ELAPSED_TIME);
    if(!Game.Loop()) exit(0);
    int et = glutGet(GLUT_ELAPSED_TIME);
    int elapsed = et - st;
    if (elapsed < 1000 / 60)
    {
#ifdef WIN32
        Sleep(1000 / 60 - elapsed);
#else
        std::this_thread::sleep_for(std::chrono::microseconds(100000/60 - elapsed*1000));
#endif
        
    }

}

int main(int argc, char** argv)
{
    int res_x,res_y,pos_x,pos_y;

    //GLUT initialization
    glutInit(&argc, argv);

    //RGBA with double buffer
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

    //Create centered window
    res_x = glutGet(GLUT_SCREEN_WIDTH);
    res_y = glutGet(GLUT_SCREEN_HEIGHT);
    pos_x = (res_x>>1)-(GAME_WIDTH);
    pos_y = (res_y>>1)-(GAME_HEIGHT);
    
    glutInitWindowPosition(pos_x,pos_y);
    glutInitWindowSize(GAME_WIDTH*2,GAME_HEIGHT*2);
    glutCreateWindow("The Legend of Zelda");

    /*glutGameModeString("800x600:32");
    glutEnterGameMode();*/

    //Make the default cursor disappear
    //glutSetCursor(GLUT_CURSOR_NONE);

    //Register callback functions
    glutDisplayFunc(AppRender);            
    glutKeyboardFunc(AppKeyboard);        
    glutKeyboardUpFunc(AppKeyboardUp);    
    glutSpecialFunc(AppSpecialKeys);    
    glutSpecialUpFunc(AppSpecialKeysUp);
    glutMouseFunc(AppMouse);
    glutIdleFunc(AppIdle);

    //Game initializations
    Game.Init();

    //Application loop
    glutMainLoop();    
}
