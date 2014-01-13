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
#pragma warning("TODO - URGENT")
//	videoFlags = SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT;

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
#pragma warning("TODO - URGENT")
//		fullscreen = SDL_FULLSCREEN;
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
#pragma warning("TODO - URGENT")
//		fullscreen = SDL_FULLSCREEN;
	}
	setVideo();
}


SDL_Surface* DisplayManager::getScreen() const
{
    return screen;
}

void DisplayManager::Flip()
{
	if(openGL)
	{
#pragma warning("TODO - URGENT")
//		SDL_GL_SwapBuffers();
	}
	else
	{
#pragma warning("TODO - URGENT")
//		SDL_Flip(screen);
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
#pragma warning("TODO - URGENT")
//	screen = SDL_SetVideoMode(w, h, bpp, videoFlags | fullscreen);
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
#pragma warning("TODO - URGENT")
//		videoFlags = SDL_OPENGL | fullscreen;
	}
	else
	{
		openGL = false;
#pragma warning("TODO - URGENT")
//		videoFlags =  SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ASYNCBLIT | fullscreen;
	}
}

void DisplayManager::Init(bool Fullscreen, bool UsingOpenGL)
{
	FullScreen(Fullscreen);
	useOpengGL(UsingOpenGL);
	setVideo();
	assert(screen);
}

void DisplayManager::clearDisplay()
{
	if(openGL)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

};
