#ifndef WD_SDL_IMAGE_HPP_DEFINED
#define WD_SDL_IMAGE_HPP_DEFINED

#ifdef WIN32
    #include <windows.h>
#endif //_WIN32

#include <string>

#include "WarpDrive/display/rgbcolour.hpp"
#include "WarpDrive/basesystem/displaymanager.hpp"
#include "WarpDrive/basemaths/rect.hpp"
#include "WarpDrive/basemaths/vec2.hpp"

struct SDL_Texture;

class SDLImage
{
public:
    SDLImage();

    virtual ~SDLImage();

    bool load(const std::string& filename);

    void setColourKey(const SDLRGBColour& tc = SDLRGBColour(0,255,255));//default = Pure Cyan

    void blit(int xPos = 0, int yPos = 0);

    void setAlphaT(unsigned int i = 128) {alphaT = i;}
    void setDrawAlpha(uint8_t i);
    bool isPixTransparent(int atX, int atY) const;
    SDL_Texture* Texture() {return image;}
    unsigned int PixelColour(int atX, int atY) const;
    Rectf Box() const;
    Vec2f Position()const;


protected:

    SDL_Texture* image;
    SDL_Surface* surface;
    unsigned int alphaT; //The threshold above which a pixel is considered transparent. default 128 (50%)
    int x,y;
};

#endif //WD_SDL_IMAGE_HPP_DEFINED
