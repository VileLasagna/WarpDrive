
#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include "BaseSystem/DisplayManager.hpp"
#include "BaseSystem/Game.hpp"
#include "BaseSystem/TeapotLoaderState.hpp"


int main(/*int argc, char* argv[]*/)
{

    //glutInit(&argc, argv);
    DisplayManager::instance()->setSize(1280,728);
    DisplayManager::instance()->Init(false,true);
    Game::instance()->addState(new TeapotLoaderState());

    Game::instance()->showFPS(false);
    Game::instance()->Run();

    Game::instance()->Clear();


    return 0;
}
