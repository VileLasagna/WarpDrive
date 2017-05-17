#ifndef WD_RECT_HPP_DEFINED
#define WD_RECT_HPP_DEFINED

#include "WarpDrive/display/rgbacolour.hpp"

template <typename T>
class Rect
{
public:
    constexpr Rect() : mX(0), MX(0), mY(0), MY(0) {}

    constexpr Rect(T minX, T maxX, T minY, T maxY) :
            mX(minX), MX(maxX), mY(minY), MY(maxY) {}

    constexpr T MinX() const noexcept { return mX; }
    constexpr T MaxX() const noexcept { return MX; }
    constexpr T MinY() const noexcept { return mY; }
    constexpr T MaxY() const noexcept { return MY; }

    constexpr T Width() const  noexcept { return MX - mX; }
    constexpr T Height() const noexcept { return MY - mY; }

    constexpr void setColour (const SDLRGBAColour& c) noexcept {colour = c;}

    constexpr bool intersects(const Rect<T>& rhs) const noexcept
    {
        return ( MinX()     <= rhs.MaxX() &&
                rhs.MinX()  <=   MaxX()   &&
                MinY()      <= rhs.MaxY() &&
                rhs.MinY()  <=   MaxY()     );


    }

private:
    T mX, MX, mY, MY;
    SDLRGBAColour colour;
};

using Rectf = Rect<float>;
using Recti = Rect<int>;

#endif //WD_RECT_HPP_DEFINED
