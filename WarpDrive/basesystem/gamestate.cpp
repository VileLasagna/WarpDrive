#include "WarpDrive/basesystem/gamestate.hpp"

#include <SDL2/SDL_events.h>

void GameState::onKeyboardEvent(const SDL_KeyboardEvent& e)
{
    if (e.keysym.sym == SDLK_ESCAPE)
    {
        onQuitEvent();
    }
}
