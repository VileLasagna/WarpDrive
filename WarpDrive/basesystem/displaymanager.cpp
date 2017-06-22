#include "WarpDrive/basesystem/displaymanager.hpp"

#include <assert.h>
#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

#include "WarpDrive/basesystem/game.hpp"
#include "WarpDrive/basesystem/stringproc.hpp"

DisplayManager::DisplayManager():
    mainWindow  (0),
    renderer    (0),
    gl_context  (0),
    dt          (0),
    maxDT       (67),
    openGL      (false),
    vsync       (false),
    bpp         (32),
    w           (640),
    h           (480),
    modelview   (new GLdouble[16]),
    projection  (new GLdouble[16]),
    viewport    (new GLint[4]),
    fullscreen  (0),
    videoFlags  (0)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    //videoFlags = 0/*SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT*/;

    int numJs = SDL_NumJoysticks();
    for (int i = 0; i < numJs; i++)
    {
        SDL_JoystickOpen(i);
    }
    SDL_JoystickEventState(SDL_ENABLE);
}

DisplayManager::~DisplayManager()
{
    delete[] modelview;
    delete[] projection;
    delete[] viewport;
    SDL_Quit();
}

void DisplayManager::setFullscreen(bool b)
    {
    if (b)
    {
        fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    else
    {
        fullscreen = 0;
    }
}

void DisplayManager::toggleFS()
{
    if (fullscreen)
    {
        fullscreen = 0;
    }
    else
    {
        fullscreen = SDL_WINDOW_FULLSCREEN_DESKTOP;
    }
    setVideo();
}

void DisplayManager::showStats(unsigned int updates, unsigned int frames) noexcept
{
    if(!mainWindow)
    {
        return;
    }
    else
    {
        std::string title = "Warp Drive :: UPS: "+ StringProc::intToString( static_cast<int>(updates) )
                          + "  FPS: "+StringProc::intToString( static_cast<int>(frames) );
        SDL_SetWindowTitle(mainWindow, title.c_str());
    }
}

void DisplayManager::setTitle(std::string newTitle, int) noexcept
{
    //second argument is for when we're supporting multiple windows
     SDL_SetWindowTitle(mainWindow, newTitle.c_str());
}

SDL_Window* DisplayManager::Screen() const
{
    return mainWindow;
}

SDL_Renderer* DisplayManager::Renderer() const
{
    return renderer;
}

void DisplayManager::Flip()
{
    if(openGL)
    {
        SDL_GL_SwapWindow(mainWindow);
    }
    else
    {
        SDL_RenderPresent(renderer);
    }
}

void DisplayManager::Update()
{
    static Game::time_t lastCall = Game::instance()->now();
    dt = Game::instance()->millisSince(lastCall);
    if (dt > maxDT)
    {
        dt = maxDT;
    }
    lastCall = Game::instance()->now();
}

float DisplayManager::Dt() const noexcept
{
    return dt;
}

float DisplayManager::DtSecs() const noexcept
{
    return dt/1000.f;
}

DisplayManager* DisplayManager::instance()
{
    static DisplayManager* inst = 0;
    if (!inst)
    {
        inst = new DisplayManager;
    }
    return inst;
}

void DisplayManager::clear() noexcept
{
    delete(DisplayManager::instance());
    //yeah, I know this might end up initialising this unnecessarily
    //but I couldn't really find an alternative
}

void DisplayManager::setSize(int width, int height)
{
    w = width;
    h = height;
    if(mainWindow)
    {
        SDL_SetWindowSize(mainWindow, w, h);
    }
}

void DisplayManager::setVideo()
{
    //TODO: This is not properly structured for multiple window support
    if(!fullscreen)
    {
        mainWindow = SDL_CreateWindow(
                "Warp Drive",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                w, h,
                videoFlags);
    }
    else
    {
        mainWindow = SDL_CreateWindow(
                "Warp Drive",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                0,0,
                fullscreen);
    }
}

void DisplayManager::applyVsync()
{
    if(vsync)
    {
        SDL_GL_SetSwapInterval(1);
    }
    else
    {
        SDL_GL_SetSwapInterval(0);
    }
}

void DisplayManager::setBPP(int i)
{
    bpp = i;
    setVideo();
}

void DisplayManager::useOpengGL(bool b) noexcept
{
    if (b)
    {
        openGL = true;
        videoFlags = SDL_WINDOW_OPENGL | fullscreen;
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        openGL = false;
        videoFlags =  0/*DL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT */| fullscreen;
    }
}

void DisplayManager::setVsync(bool v) noexcept
{
    vsync = v;
    applyVsync();
}

void DisplayManager::toggleVsync() noexcept
{
    vsync = !vsync;
    applyVsync();
}

void DisplayManager::init(bool Fullscreen, bool UsingOpenGL) noexcept
{
    setFullscreen(Fullscreen);
    useOpengGL(UsingOpenGL);
    setVideo();
    if(!openGL)
    {
        renderer = SDL_CreateRenderer(mainWindow, -1, 0);
    }
    else
    {
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
        gl_context = SDL_GL_CreateContext(mainWindow);
        SDL_GL_MakeCurrent(mainWindow, gl_context);
        applyVsync();
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK)
        {
           std::cout << "Failed to initialize GLEW" << std::endl;
        }
    }
    assert(mainWindow);
}

void DisplayManager::updateMatrices()
{
    glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
    glGetDoublev(GL_PROJECTION_MATRIX,projection);
    glGetIntegerv(GL_VIEWPORT,viewport);
}

void DisplayManager::clearDisplay() noexcept
{
    if(openGL)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}
