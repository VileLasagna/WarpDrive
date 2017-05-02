#ifndef WD_SDLTTF_HPP_DEFINED
#define WD_SDLTTF_HPP_DEFINED

#include <string>
#include <SDL2/SDL_ttf.h>

#include "WarpDrive/basesystem/displaymanager.hpp"
#include "WarpDrive/display/texture.hpp"

class SDLTTF
{
public:
	SDLTTF();
	~SDLTTF();

    bool load(const std::string& fontFileName, int pointSize);
    void draw(const std::string& text, Texture* target) const;
	//void setColour( int r, int g, int b);

private:

	TTF_Font* font;
	SDL_Colour colour; //standard = white
};

#endif //WD_SDLTTF_HPP_DEFINED
