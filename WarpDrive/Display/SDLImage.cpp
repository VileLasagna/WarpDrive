#include "SDLImage.h"
#ifdef _WIN32
	#include <SDL/SDL_Image.h>
#else
	#include <SDL2/SDL_image.h>
#endif //_WIN32
#include <assert.h>

SDLImage::SDLImage()
{
    image = 0;
    surface = 0;
	setAlphaT();
	x = 0;
	y = 0;
}

bool SDLImage::Load(const std::string& filename)
{
    surface = IMG_Load(filename.c_str());
    image = SDL_CreateTextureFromSurface(DisplayManager::instance()->getRenderer(), surface);

    return (image != 0);
}

void SDLImage::setColourKey(const SDLRGBColour& tc)
{
    SDL_SetColorKey(
        surface,
        SDL_TRUE | SDL_RLEACCEL,
        SDL_MapRGB(surface->format, tc.R(), tc.G(), tc.B()));
    image = SDL_CreateTextureFromSurface(DisplayManager::instance()->getRenderer(), surface);

}

SDLImage::~SDLImage()
{
	
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(image);
	
}

void SDLImage::Blit(int x, int y)
{
	this->x = x;
	this->y = y;
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    SDL_RenderCopy(DisplayManager::instance()->getRenderer(), image, 0, &dest );
}

Rectf SDLImage::getBox() const
{
    return Rectf(x,surface->w,y,surface->h);
}

Vec2f SDLImage::getPos() const
{
	return Vec2f(x,y);
}

void SDLImage::setDrawAlpha(int i)
{
    SDL_SetTextureAlphaMod(image, i);
}

unsigned int SDLImage::getPixelColour(int x, int y) const
{
	unsigned char* c = 
        (unsigned char*) surface->pixels +
        (y * surface->pitch) +
        (x * surface->format->BytesPerPixel);

	unsigned int r = 0;
    if (surface->format->BytesPerPixel == 3)
    {
        r = c[0] + (c[1] << 8) + (c[2] << 16);
    }
    else if (surface->format->BytesPerPixel == 4)
    {
        r = c[0] + (c[1] << 8) + (c[2] << 16) + (c[3] << 24);
    }
    return r;
}

bool SDLImage::isPixTransparent(int x, int y) const
{
    unsigned int r = getPixelColour(x, y);

    if (surface->format->BytesPerPixel <= 3)
    {
        // No alpha channel - check if colour is same as colour key
        //return (r == image->format->colorkey);
        return false;
    }

    // Image has alpha channel, so pixel is transparent if alpha is lesser than the set threshold
    return ((r & 0xff000000) <= alphaT);
}
