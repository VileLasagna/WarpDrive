
#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include "basesystem/displaymanager.hpp"
#include "basesystem/game.hpp"
#include "gldemostate.hpp"


int main(/*int argc, char* argv[]*/)
{

    //glutInit(&argc, argv);
    DisplayManager::instance()->setSize(1280,728);
    DisplayManager::instance()->init(false,true);
    Game::instance()->addState(new GLDemoState());

    Game::instance()->showFPS(true);
    Game::instance()->Run();

    Game::instance()->Clear();


    return 0;
}