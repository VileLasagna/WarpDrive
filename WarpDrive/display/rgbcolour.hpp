#ifndef SDL_COLOUR_H
#define SDL_COLOUR_H

template <typename T> class RGBColour
{
public:
	constexpr explicit RGBColour(
			 T red   = 0,
			 T green = 0,
			 T blue  = 0   ):
		r{red},
		g{green},
		b{blue} {}
	constexpr T R() const{ return r; }
	constexpr T G() const{ return g; }
	constexpr T B() const{ return b; }


protected:
    T r,g,b;
};

using SDLRGBColour = RGBColour<unsigned int>;
using GLRGBColour = RGBColour<float>;


#endif