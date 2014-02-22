#include "DisplayManager.h"

#include <assert.h>


DisplayManager::DisplayManager()
{
    dt = 0;
	bpp = 32;
	w = 640;
	h = 480;
    SDL_Init(SDL_INIT_EVERYTHING);	
	maxDT = 0.05f;
	fullscreen = 0;
    renderer = 0;
    gl_context = 0;
    videoFlags = 0/*SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT*/;

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


SDL_Window* DisplayManager::getScreen() const
{
    return screen;
}

SDL_Renderer* DisplayManager::getRenderer() const
{
    return renderer;
}

void DisplayManager::Flip()
{
	if(openGL)
	{
        SDL_GL_SwapWindow(screen);
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
	setVideo();
}

void DisplayManager::setVideo()
{

    if(!fullscreen)
    {
        screen = SDL_CreateWindow(
                "Warp Drive",
                SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED,
                w, h,
                videoFlags);
    }
    else
    {
        screen = SDL_CreateWindow(
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
        renderer = SDL_CreateRenderer(screen, -1, 0);
    }
    else
    {
        gl_context = SDL_GL_CreateContext(screen);
        SDL_GL_MakeCurrent(screen, gl_context);
    }
	assert(screen);
}

void DisplayManager::clearDisplay()
{
	if(openGL)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

};
