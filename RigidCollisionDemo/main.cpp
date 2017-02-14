
#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include "basesystem/displaymanager.hpp"
#include "basesystem/game.hpp"
#include "launcherstate.hpp"

int main(int argc, char* argv[])
{

    DisplayManager::instance()->setSize(1280,728);
    DisplayManager::instance()->init(false,true);
    Game::instance()->addState(new LauncherState());

    Game::instance()->showFPS(true);
    Game::instance()->Run();

    Game::instance()->Clear();


    return 0;
}
