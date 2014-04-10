
#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include "BaseSystem/DisplayManager.h"
#include "BaseSystem/Game.h"
#include "BaseSystem/TeapotLoaderState.h"


int main(int argc, char* argv[])
{

    glutInit(&argc, argv);
    DisplayManager::instance()->setSize(1280,728);
    DisplayManager::instance()->Init(false,true);
    Game::instance()->addState(new TeapotLoaderState());

    Game::instance()->showFPS();
    Game::instance()->Run();

    Game::instance()->Clear();


    return 0;
}
