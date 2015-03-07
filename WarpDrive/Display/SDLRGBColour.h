#ifndef SDL_COLOUR_H
#define SDL_COLOUR_H

class SDLRGBColour
{
public:
	constexpr explicit SDLRGBColour(
			unsigned int red   = 0,
			unsigned int green = 0,
			unsigned int blue  = 0   ):
		r{red},
		g{green},
		b{blue} {}
	constexpr auto R() const{ return g; }
	constexpr auto G() const{ return g; }
	constexpr auto B() const{ return b; }


protected:
    unsigned int r,g,b;
};


#endif
