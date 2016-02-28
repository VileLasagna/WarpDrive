#include <assert.h>
#include "BaseSystem/SDLEventHandler.hpp"
#include "BaseSystem/DisplayManager.hpp"

void SDLEventHandler::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		HandleEvent(event);
	}
}

void SDLEventHandler::HandleEvent(const SDL_Event& e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
	case SDL_KEYUP:
		onKeyboardEvent(e.key);
		break;

	case SDL_MOUSEMOTION:
		onMouseMotionEvent(e.motion);
		break;

	case SDL_MOUSEBUTTONDOWN:
	case SDL_MOUSEBUTTONUP:
		onMouseButtonEvent(e.button);
		break;

	case SDL_QUIT:
		onQuitEvent();
		break;

	case SDL_JOYAXISMOTION:
		onJoyAxisEvent(e.jaxis);
		break;

	case SDL_JOYBUTTONDOWN:
	case SDL_JOYBUTTONUP:
		onJoyButtonEvent(e.jbutton);
		break;

    case SDL_JOYHATMOTION:
        onJoyHatEvent(e.jhat);
        break;

    case SDL_JOYBALLMOTION:
        onJoyBallEvent(e.jball);
        break;
    case SDL_WINDOWEVENT:
        onWindowEvent(e.window);
        break;

	default:
        // Unexpected event type!
        //assert(0);
		break;
	}
}

void SDLEventHandler::onQuitEvent()
{
    exit(0);
}

void SDLEventHandler::onWindowEvent(const SDL_WindowEvent& e)
{
    /*
     *SDL provides two "resize" events.
     * Warp Drive only provides treatment for the "resize request"
     * type, for the moment. Should it prove useful, this will be ammended
     */
    if (e.windowID != SDL_GetWindowID(DisplayManager::instance()->getScreen()))
    {
        return;
    }

    switch (e.event)
    {
        case SDL_WINDOWEVENT_SHOWN:
            onWindowShown(e);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            onWindowHidden(e);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            onWindowExposed(e);
            break;
        case SDL_WINDOWEVENT_MOVED:
            onWindowMoved(e);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            onWindowResized(e);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            onWindowMinimized(e);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            onWindowMaximized(e);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            onWindowRestored(e);
            break;
        case SDL_WINDOWEVENT_ENTER:
            onMouseEntered(e);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            onMouseLeft(e);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            onKeyboardFocus(e);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            onKeyboardFocusLost(e);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            onWindowCloseRequest(e);
            break;
    default:
        // Unexpected event type!
        assert(0);
        break;
    }
}
