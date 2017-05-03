#include <assert.h>
#include "WarpDrive/display/sdlttf.hpp"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>

struct FontInitialiser
{
	FontInitialiser()
	{
		TTF_Init();
	}
};

SDLTTF::SDLTTF()
   :color{new SDL_Colour{255,255,255,255}},
    font{nullptr}
{}

SDLTTF::~SDLTTF()
{
	if (font)
	{
		TTF_CloseFont(font);
	}
    if(color)
    {
        delete color;
    }
}

bool SDLTTF::load(const std::string& fontFileName, int pointSize)
{
	font = TTF_OpenFont(fontFileName.c_str(), pointSize);
	assert(font);
	return (font != 0);
}

void SDLTTF::draw(const std::string& text, Texture* target) const
{
	assert(font);

	SDL_Surface* pSurface = TTF_RenderText_Blended(
		font, 
		text.c_str(), 
        *color);

    target->createFromSDLSurface(pSurface);

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
