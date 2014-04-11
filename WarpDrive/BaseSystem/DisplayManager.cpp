#include "BaseSystem/DisplayManager.h"
#include "BaseSystem/StringProc.h"

#include <assert.h>


DisplayManager::DisplayManager():
    dt          (0),
    bpp         (32),
    w           (640),
    h           (480),
    maxDT       (0.05f),
    fullscreen  (0),
    renderer    (0),
    gl_context  (0),
    videoFlags  (0),
    mainWindow  (0)
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
	SDL_Quit();
}

void DisplayManager::FullScreen(bool b)
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


void DisplayManager::ToggleFS()
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

void DisplayManager::showStats(int updates, int frames)
{
    if(!mainWindow)
    {
        return;
    }
    else
    {
        std::string title = "Warp Drive :: UPS: "+ StringProc::intToString(updates)+"  FPS: "+StringProc::intToString(frames);
        SDL_SetWindowTitle(mainWindow, title.c_str());
    }
}

void DisplayManager::setTitle(std::string newTitle, int)
{
    //second argument is for when we're supporting multiple windows
     SDL_SetWindowTitle(mainWindow, newTitle.c_str());
}

SDL_Window* DisplayManager::getScreen() const
{
    return mainWindow;
}

SDL_Renderer* DisplayManager::getRenderer() const
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
    static unsigned int oldms = SDL_GetTicks();
    unsigned int ms = SDL_GetTicks();
    dt = ((float)(ms - oldms)) / 1000.0f;
    oldms = ms;
	if (dt > maxDT)
	{
		dt = maxDT;
	}
}

float DisplayManager::getDtSecs() const
{
    return dt;
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

void DisplayManager::clear()
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

void DisplayManager::setBPP(int i)
{
	bpp = i;
	setVideo();
}

void DisplayManager::useOpengGL(bool b)
{
	if (b)
	{
		openGL = true;
        videoFlags = SDL_WINDOW_OPENGL | fullscreen;
	}
	else
	{
		openGL = false;
        videoFlags =  0/*DL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT */| fullscreen;
	}
}

void DisplayManager::Init(bool Fullscreen, bool UsingOpenGL)
{
	FullScreen(Fullscreen);
	useOpengGL(UsingOpenGL);
	setVideo();
    if(!openGL)
    {
        renderer = SDL_CreateRenderer(mainWindow, -1, 0);
    }
    else
    {
        gl_context = SDL_GL_CreateContext(mainWindow);
        SDL_GL_MakeCurrent(mainWindow, gl_context);
    }
    assert(mainWindow);
}

void DisplayManager::clearDisplay()
{
	if(openGL)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

};
