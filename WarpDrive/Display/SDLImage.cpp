#include "SDLImage.h"
#include <SDL/SDL_Image.h>
#include <assert.h>

SDLImage::SDLImage()
{
    image = 0;
	setAlphaT();
	x = 0;
	y = 0;
}

bool SDLImage::Load(const std::string& filename)
{
    image = IMG_Load(filename.c_str());

    return (image != 0);
}

void SDLImage::setColourKey(const SDLRGBColour& tc)
{
#pragma warning("TODO - URGENT")
/**	SDL_SetColorKey(
        image, 
        SDL_SRCCOLORKEY | SDL_RLEACCEL, 
		SDL_MapRGB(image->format, tc.R(), tc.G(), tc.B()));
        */
}

SDLImage::~SDLImage()
{
	
    SDL_FreeSurface(image);
	
}

void SDLImage::Blit(int x, int y)
{
	this->x = x;
	this->y = y;
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
	SDL_BlitSurface(image, 0, DisplayManager::instance()->getScreen(), &dest);
}

Rectf SDLImage::getBox() const
{
	return Rectf(x,image->w,y,image->h);
}

Vec2f SDLImage::getPos() const
{
	return Vec2f(x,y);
}

void SDLImage::setDrawAlpha(int i)
{
#pragma warning("TODO - URGENT")
//	SDL_SetAlpha(image, SDL_SRCALPHA | SDL_RLEACCEL , i);
}

unsigned int SDLImage::getPixelColour(int x, int y) const
{
	unsigned char* c = 
        (unsigned char*) image->pixels + 
        (y * image->pitch) +
        (x * image->format->BytesPerPixel);

	unsigned int r = 0;
    if (image->format->BytesPerPixel == 3)
    {
        r = c[0] + (c[1] << 8) + (c[2] << 16);
    }
    else if (image->format->BytesPerPixel == 4)
    {
        r = c[0] + (c[1] << 8) + (c[2] << 16) + (c[3] << 24);
    }

    return r;
}

bool SDLImage::isPixTransparent(int x, int y) const
{
    unsigned int r = getPixelColour(x, y);

    if (image->format->BytesPerPixel <= 3)
    {
        // No alpha channel - check if colour is same as colour key
#pragma warning("TODO - URGENT")
//return (r == image->format->colorkey);
        return false;
    }

    // Image has alpha channel, so pixel is transparent if alpha is lesser than the set threshold
    return ((r & 0xff000000) <= alphaT);
}
