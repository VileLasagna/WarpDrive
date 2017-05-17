#ifndef WD_SDLRGBACOLOUR_HPP_DEFINED
#define WD_SDLRGBACOLOUR_HPP_DEFINED

#include<cstdint>

#include "WarpDrive/display/rgbcolour.hpp"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"

template <typename T> class RGBAColour

{
public:

    constexpr RGBAColour(	T red   = 0,
                            T green = 0,
                            T blue  = 0,
                            T alpha = 255 ):
                            a{alpha}{ SDLRGBColour(static_cast<T>(red),static_cast<T>(green),static_cast<T>(blue));}

    constexpr T R() const {return r;}
    constexpr T G() const {return g;}
    constexpr T B() const {return b;}
    constexpr T A() const {return a;}

    operator RGBColour<T>() { return RGBColour<T>(r,g,b);}

protected:

    T r,g,b,a;
};

using SDLRGBAColour = RGBAColour<uint8_t>;
using GLRBGAColour = RGBAColour<float>;

#pragma clang diagnostic pop

#endif //WD_SDLRGBACOLOUR_HPP_DEFINED
