#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL/SDL.h>

class SDLEventHandler
{
public:
    virtual ~SDLEventHandler() {}

    void Update();
    void HandleEvent(const SDL_Event& event);

protected:
    virtual void onKeyboardEvent(const SDL_KeyboardEvent& ) {}
    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent& ) {}
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent& ) {}
    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent& ) {}
    virtual void onJoyBallEvent(const SDL_JoyBallEvent& ) {}
    virtual void onJoyHatEvent(const SDL_JoyHatEvent& ) {}
    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent& ) {}
    //virtual void onActiveEvent (const SDL_ActiveEvent& ) {}
    //virtual void onExposeEvent (const SDL_ExposeEvent& ) {}
    //virtual void onResizeEvent (const SDL_ResizeEvent& ) {}
    virtual void onQuitEvent();
};

#endif //EVENT_HANDLER_H
