#ifndef SDLTTF_H
#define SDLTTF_H

#include <string>
#include "DisplayManager.h"
#include "SDL_ttf.h"
#include "Texture.h"

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
