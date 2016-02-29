#ifndef SDLTTF_H
#define SDLTTF_H

#include <string>
#include "basesystem/displaymanager.hpp"
#include <SDL/SDL_ttf.h>
#include "display/texture.hpp"

class SDLTTF
{
public:
	SDLTTF();
	~SDLTTF();

	bool Load(const std::string& fontFileName, int pointSize);
	void Draw(const std::string& text, Texture* target);
	//void setColour( int r, int g, int b);

private:
	TTF_Font* font;
	SDL_Colour colour; //standard = white
};

#endif //SDLTTF_H
