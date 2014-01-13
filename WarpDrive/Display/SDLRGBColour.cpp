#include "SDLRGBColour.h"

SDLRGBColour::SDLRGBColour(
    unsigned int r, 
    unsigned int g, 
    unsigned int b)
{
    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
}

unsigned int SDLRGBColour::R() const
{
    return rgb[0]; 
}

unsigned int SDLRGBColour::G() const
{
    return rgb[1]; 
}

unsigned int SDLRGBColour::B() const
{
    return rgb[2]; 
}
