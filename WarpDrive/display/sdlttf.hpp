#ifndef WD_SDLTTF_HPP_DEFINED
#define WD_SDLTTF_HPP_DEFINED

#include <string>

#include "WarpDrive/basesystem/displaymanager.hpp"
#include "WarpDrive/display/texture.hpp"
#include "WarpDrive/display/rgbacolour.hpp"

using TTF_Font = struct _TTF_Font;
struct SDL_Color;

class SDLTTF
{
public:
    SDLTTF();
    ~SDLTTF();

    bool load(const std::string& fontFileName, int pointSize);
    void draw(const std::string& text, WDTexture* target) const;
    //void setColour( int r, int g, int b);

private:

    TTF_Font* font;
    SDL_Color* color; //standard = white
};

#endif //WD_SDLTTF_HPP_DEFINED
