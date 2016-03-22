#ifndef WD_SDLRGBACOLOUR_HPP_DEFINED
#define WD_SDLRGBACOLOUR_HPP_DEFINED

#include "display/rgbcolour.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

template <typename T> class RGBAColour: public RGBColour<T>

{
public:
	constexpr RGBAColour(	T red   = 0,
                            T green = 0,
                            T blue  = 0,
                            T alpha = 255 ):
                            a{alpha}{ SDLRGBColour(static_cast<T>(red),static_cast<T>(green),static_cast<T>(blue));}

	constexpr T A() const {return a;}
		
protected:

	T a;
};

using SDLRGBAColour = RGBAColour<unsigned int>;
using GLRBGAColour = RGBAColour<float>;

#pragma clang diagnostic pop

#endif //WD_SDLRGBACOLOUR_HPP_DEFINED
