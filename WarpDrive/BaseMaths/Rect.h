#ifndef RECT_H
#define RECT_H

#include "Display/SDLRGBAColour.h"

template <class T>
class Rect
{
public:
    Rect() : mX(0), MX(0), mY(0), MY(0) {}

    Rect(T minX, T maxX, T minY, T maxY) : 
        mX(minX), MX(maxX), mY(minY), MY(maxY) {}

    T MinX() const { return mX; }
    T MaxX() const { return MX; }
    T MinY() const { return mY; }
    T MaxY() const { return MY; }

    T Width() const { return MX - mX; }
    T Height() const { return MY - mY; }

	void setColour (SDLRGBAColour& c);

	bool intersects(const Rect<T>& r) const
	{
    return ( 
          MinX() <= r.MaxX() &&
        r.MinX() <=   MaxX() &&
          MinY() <= r.MaxY() &&
        r.MinY() <=   MaxY() );

	}

private:
    T mX, MX, mY, MY;
	SDLRGBAColour colour;
};

typedef Rect<float> Rectf;
typedef Rect<int> Recti;

#endif
