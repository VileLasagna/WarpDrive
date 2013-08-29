#include <assert.h>
#include "EventHandler.h"

void EventHandler::Update()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		HandleEvent(event);
	}
}

void EventHandler::HandleEvent(const SDL_Event& e)
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
	case SDL_ACTIVEEVENT:
		onActiveEvent (e.active);
		break;
	case SDL_VIDEOEXPOSE:
		onExposeEvent (e.expose);
		break;
	case SDL_VIDEORESIZE:
		onResizeEvent(e.resize);
		break;

	default:
        // Unexpected event type!
		assert(0);
		break;
	}
}

void EventHandler::onQuitEvent()
{
    exit(0);
}