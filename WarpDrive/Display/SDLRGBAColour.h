#ifndef SDLRGBACOLOUR_H
#define SDLRGBACOLOUR_H

#include "Display/SDLRGBColour.h"


class SDLRGBAColour: public SDLRGBColour

{
public:
	constexpr SDLRGBAColour(	unsigned int red   = 0,
						unsigned int green = 0,
						unsigned int blue  = 0,
						unsigned int alpha = 255 ):
						a{alpha}{ SDLRGBColour(red,green,blue);}

	constexpr auto A() const {return a;}
		
protected:

	unsigned int a;
};

#endif //SDLRGBACOLOUR_H
