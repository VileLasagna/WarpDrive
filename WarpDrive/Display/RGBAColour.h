#ifndef SDLRGBACOLOUR_H
#define SDLRGBACOLOUR_H

#include "Display/RGBColour.h"


template <typename T> class RGBAColour: public RGBColour<T>

{
public:
	constexpr RGBAColour(	T red   = 0,
						T green = 0,
						T blue  = 0,
						T alpha = 255 ):
						a{alpha}{ SDLRGBColour(red,green,blue);}

	constexpr T A() const {return a;}
		
protected:

	T a;
};

using SDLRGBAColour = RGBAColour<unsigned int>;
using GLRBGAColour = RGBAColour<float>;

#endif //SDLRGBACOLOUR_H
