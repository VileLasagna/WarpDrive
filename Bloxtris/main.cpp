//#include "Game.h"
//
//
//int main(int numargs, char** args)
//{
//
//
//
//	return 0;
//}

#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include "basesystem/DisplayManager.h"
#include "basesystem/Game.h"
#include "basesystem/TeapotLoaderState.h"

//#include <GL/glut.h>
#include "MainGS.h"
#include "Splash.h"
#include "GOScreen.h"
#include "DemoState.h"

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char* argv[])
{

    //glutInit(&argc, argv);
	DisplayManager::instance()->setSize(1280,728);
	DisplayManager::instance()->Init(false,true);
    Game::instance()->addState(new Splash);
    Game::instance()->addState(new MainGS);
    Game::instance()->addState(new GOScreen);
    Game::instance()->addState(new DemoState);
    //Game::instance()->addState(new TeapotLoaderState());

    Game::instance()->showFPS();
	Game::instance()->Run();
	
    Game::instance()->Clear();

        
    return 0;
}
