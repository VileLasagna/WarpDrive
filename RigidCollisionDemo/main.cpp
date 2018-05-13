
#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include "WarpDrive/basesystem/displaymanager.hpp"
#include "WarpDrive/basesystem/game.hpp"
#include "launcherstate.hpp"

int main(int argc, char* argv[])
{

    DisplayManager::instance()->setSize(800,600);
    DisplayManager::instance()->init(false,true);
    Game::instance()->addState(new LauncherState());

    Game::instance()->setLogFileName("PhysicsDemo.err");
    Game::instance()->showFPS(true);
    Game::instance()->Run();

    Game::instance()->Clear();


    return 0;
}
