#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H

#include <SDL.h>
#include <string>
#include "SDLRGBColour.h"
#include "DisplayManager.h"
#include "Rect.h"
#include "Vec2.h"

class SDLImage
{
public:
    SDLImage();
    
    virtual ~SDLImage();

    bool Load(const std::string& filename);

	void setColourKey(const SDLRGBColour& tc = SDLRGBColour::SDLRGBColour(0,255,255));//default = Pure Cyan

    void Blit(int x = 0, int y = 0);

	void setAlphaT(int i = 128) {alphaT = i;}
	void setDrawAlpha(int i);
	bool isPixTransparent(int x, int y) const;
	SDL_Surface* getSurf() {return image;}
	unsigned int getPixelColour(int x, int y) const;
	Rectf getBox() const;
	Vec2f getPos()const;


protected:
    SDL_Surface* image;
	unsigned int alphaT; //The threshold above which a pixel is considered transparent. default 128 (50%)
	int x,y;
};

#endif
