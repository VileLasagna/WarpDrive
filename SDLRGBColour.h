#ifndef SDL_COLOUR_H
#define SDL_COLOUR_H

class SDLRGBColour
{
public:
    SDLRGBColour(
        unsigned int r = 0, 
        unsigned int g = 0, 
        unsigned int b = 0);

    unsigned int R() const;
    unsigned int G() const;
    unsigned int B() const;

protected:
    unsigned int rgb[3];
};

#endif
