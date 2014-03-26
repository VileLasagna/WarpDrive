#ifndef SDLRGBACOLOUR_H
#define SDLRGBACOLOUR_H

#include "Display/SDLRGBColour.h"


class SDLRGBAColour: public SDLRGBColour

{
public:
	    SDLRGBAColour(
        unsigned int r = 0, 
        unsigned int g = 0, 
        unsigned int b = 0,
		unsigned int a = 255) 
		{    
			rgb[0] = r;
			rgb[1] = g;
			rgb[2] = b;
			alpha = a;
		}

		unsigned int A() const {return alpha;}
		
protected:

	unsigned int alpha;
};

#endif //SDLRGBACOLOUR_H
