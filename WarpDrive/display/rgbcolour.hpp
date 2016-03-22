#ifndef WD_SDL_COLOUR_HPP_DEFINED
#define WD_SDL_COLOUR_HPP_DEFINED

template <typename T> class RGBColour
{
public:
    constexpr explicit RGBColour(T red   = 0,
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

using SDLRGBColour = RGBColour<unsigned short>;
using GLRGBColour = RGBColour<float>;

#endif //WD_SDL_COLOUR_HPP_DEFINED
