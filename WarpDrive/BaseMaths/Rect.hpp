#ifndef RECT_H
#define RECT_H

#include "Display/RGBAColour.hpp"

template <class T>
class Rect
{
public:
	constexpr Rect() : mX(0), MX(0), mY(0), MY(0) {}

	constexpr Rect(T minX, T maxX, T minY, T maxY) :
			mX(minX), MX(maxX), mY(minY), MY(maxY) {}

	constexpr T MinX() const { return mX; }
	constexpr T MaxX() const { return MX; }
	constexpr T MinY() const { return mY; }
	constexpr T MaxY() const { return MY; }

	constexpr T Width() const  { return MX - mX; }
	constexpr T Height() const { return MY - mY; }

	constexpr void setColour (const SDLRGBAColour& c) {colour = c;}

	constexpr bool intersects(const Rect<T>& rhs) const
	{
		return ( MinX()     <= rhs.MaxX() &&
			    rhs.MinX() <=   MaxX()   &&
			    MinY()     <= rhs.MaxY() &&
			    rhs.MinY() <=   MaxY()     );


	}

private:
	T mX, MX, mY, MY;
	SDLRGBAColour colour;
};

using Rectf = Rect<float>;
using Recti = Rect<int>;

#endif
