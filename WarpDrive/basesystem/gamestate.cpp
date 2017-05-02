#include "WarpDrive/basesystem/gamestate.hpp"


void GameState::onKeyboardEvent(const SDL_KeyboardEvent& e)
{
    if (e.keysym.sym == SDLK_ESCAPE)
    {
        onQuitEvent();
    }
}
