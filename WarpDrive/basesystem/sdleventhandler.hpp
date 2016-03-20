#ifndef WD_EVENT_HANDLER_HPP_DEFINED
#define WD_EVENT_HANDLER_HPP_DEFINED

#include <SDL2/SDL.h>

class SDLEventHandler
{
public:
    virtual ~SDLEventHandler() {}

    void update();
    void handleEvent(const SDL_Event& event);

protected:
    virtual void onKeyboardEvent(const SDL_KeyboardEvent& ) {}
    virtual void onMouseMotionEvent(const SDL_MouseMotionEvent& ) {}
    virtual void onMouseButtonEvent(const SDL_MouseButtonEvent& ) {}
    virtual void onJoyAxisEvent(const SDL_JoyAxisEvent& ) {}
    virtual void onJoyBallEvent(const SDL_JoyBallEvent& ) {}
    virtual void onJoyHatEvent(const SDL_JoyHatEvent& ) {}
    virtual void onJoyButtonEvent(const SDL_JoyButtonEvent& ) {}

    virtual void onMouseEntered(const SDL_WindowEvent& ) {}
    virtual void onMouseLeft(const SDL_WindowEvent& ) {}
    virtual void onWindowMaximized(const SDL_WindowEvent& ) {}
    virtual void onWindowMinimized(const SDL_WindowEvent& ) {}
    virtual void onWindowShown(const SDL_WindowEvent& ) {}
    virtual void onWindowHidden(const SDL_WindowEvent& ) {}
    virtual void onWindowExposed(const SDL_WindowEvent& ) {}
    virtual void onWindowMoved(const SDL_WindowEvent& ) {}
    virtual void onWindowResized(const SDL_WindowEvent& ) {}
    virtual void onWindowRestored(const SDL_WindowEvent& ) {}
    virtual void onKeyboardFocus(const SDL_WindowEvent& ) {}
    virtual void onKeyboardFocusLost(const SDL_WindowEvent& ) {}
    virtual void onWindowCloseRequest(const SDL_WindowEvent& ) {onQuitEvent();}

    virtual void onQuitEvent();

private:
    void onWindowEvent(const SDL_WindowEvent& );
};

#endif //WD_EVENT_HANDLER_HPP_DEFINED
