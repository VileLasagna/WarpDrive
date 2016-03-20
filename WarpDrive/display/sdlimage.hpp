#ifndef WD_SDL_IMAGE_HPP_DEFINED
#define WD_SDL_IMAGE_HPP_DEFINED

#ifdef _WIN32
    #include <windows.h>
    #include <SDL2/SDL.h>
#else
	#include <SDL2/SDL.h>
#endif //_WIN32

#include <string>

#include "display/rgbcolour.hpp"
#include "basesystem/displaymanager.hpp"
#include "basemaths/rect.hpp"
#include "basemaths/vec2.hpp"

class SDLImage
{
public:
    SDLImage();
    
	virtual ~SDLImage();

    bool load(const std::string& filename);

	void setColourKey(const SDLRGBColour& tc = SDLRGBColour(0,255,255));//default = Pure Cyan

    void blit(int x = 0, int y = 0);

	void setAlphaT(int i = 128) {alphaT = i;}
	void setDrawAlpha(int i);
	bool isPixTransparent(int x, int y) const;
    SDL_Texture* Texture() {return image;}
    unsigned int PixelColour(int x, int y) const;
    Rectf Box() const;
    Vec2f Position()const;


protected:

    SDL_Texture* image;
    SDL_Surface* surface;
	unsigned int alphaT; //The threshold above which a pixel is considered transparent. default 128 (50%)
	int x,y;
};

#endif //WD_SDL_IMAGE_HPP_DEFINED
