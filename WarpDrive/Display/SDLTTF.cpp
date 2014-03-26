#include <assert.h>
#include "Display/SDLTTF.h"


struct FontInitialiser
{
	FontInitialiser()
	{
		TTF_Init();
	}
};

SDLTTF::SDLTTF()
{
    // First call to this ctor will call initialisation function
	//...NO! Cause I moved it to the manager.
	//static FontInitialiser fi;
	SDL_Colour c = {255,255,255,255};
	//SDL_Colour c = {0,0,0,255};
	colour = c;

	font = 0;
}

SDLTTF::~SDLTTF()
{
	if (font)
	{
		TTF_CloseFont(font);
	}
}

bool SDLTTF::Load(const std::string& fontFileName, int pointSize)
{
	font = TTF_OpenFont(fontFileName.c_str(), pointSize);
	assert(font);
	return (font != 0);
}

void SDLTTF::Draw(const std::string& text, Texture* target)
{
	assert(font);

	SDL_Surface* pSurface = TTF_RenderText_Blended(
		font, 
		text.c_str(), 
		colour);

	target->CreateFromSDLSurface(pSurface);



	//SDL_Rect dest;
	/*dest.x = x;
	dest.y = y;
	SDL_BlitSurface(pSurface, 0, DisplayManager::instance()->getScreen(), &dest);*/
	SDL_FreeSurface(pSurface);
}

//void SDLTTF::setColour( int r, int g, int b)
//{
//	SDL_Colour c = { r , g , b , 255};
//	colour = c;
//}
