#ifndef SDL_IMAGE_H
#define SDL_IMAGE_H

#include <SDL/SDL.h>
#include <string>
#include "Display/SDLRGBColour.h"
#include "BaseSystem/DisplayManager.h"
#include "BaseMaths/Rect.h"
#include "BaseMaths/Vec2.h"

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
    SDL_Texture* getTexture() {return image;}
	unsigned int getPixelColour(int x, int y) const;
	Rectf getBox() const;
	Vec2f getPos()const;


protected:
    SDL_Texture* image;
    SDL_Surface* surface;
	unsigned int alphaT; //The threshold above which a pixel is considered transparent. default 128 (50%)
	int x,y;
};

#endif
