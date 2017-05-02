#include "WarpDrive/display/sdlimage.hpp"
#ifdef _WIN32
	#include <SDL2/SDL_Image.h>
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

bool SDLImage::load(const std::string& filename)
{
    surface = IMG_Load(filename.c_str());
    image = SDL_CreateTextureFromSurface(DisplayManager::instance()->Renderer(), surface);

    return (image != 0);
}

void SDLImage::setColourKey(const SDLRGBColour& tc)
{
    SDL_SetColorKey(
        surface,
        SDL_TRUE | SDL_RLEACCEL,
        SDL_MapRGB(surface->format, static_cast<unsigned char>(tc.R()), static_cast<unsigned char>(tc.G()), static_cast<unsigned char>(tc.B())));
    image = SDL_CreateTextureFromSurface(DisplayManager::instance()->Renderer(), surface);

}

SDLImage::~SDLImage()
{
	
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(image);
	
}

void SDLImage::blit(int xPos, int yPos)
{
    this->x = xPos;
    this->y = yPos;
    SDL_Rect dest;
    dest.x = xPos;
    dest.y = yPos;
    SDL_RenderCopy(DisplayManager::instance()->Renderer(), image, 0, &dest );
}

Rectf SDLImage::Box() const
{
    return Rectf(x,surface->w,y,surface->h);
}

Vec2f SDLImage::Position() const
{
	return Vec2f(x,y);
}

void SDLImage::setDrawAlpha(Uint8 i)
{
    SDL_SetTextureAlphaMod(image, i);
}

unsigned int SDLImage::PixelColour(int atX, int atY) const
{
	unsigned char* c = 
        static_cast<unsigned char*>(surface->pixels) +
        (atY * surface->pitch) +
        (atX * surface->format->BytesPerPixel);

	unsigned int r = 0;
    if (surface->format->BytesPerPixel == 3)
    {
        r = static_cast<unsigned int>(c[0] + (c[1] << 8) + (c[2] << 16));
    }
    else if (surface->format->BytesPerPixel == 4)
    {
        r = static_cast<unsigned int>(c[0] + (c[1] << 8) + (c[2] << 16) + (c[3] << 24));
    }
    return r;
}

bool SDLImage::isPixTransparent(int atX, int atY) const
{
    unsigned int r = PixelColour(atX, atY);

    if (surface->format->BytesPerPixel <= 3)
    {
        // No alpha channel - check if colour is same as colour key
        //return (r == image->format->colorkey);
        return false;
    }

    // Image has alpha channel, so pixel is transparent if alpha is lesser than the set threshold
    return ((r & 0xff000000) <= alphaT);
}
