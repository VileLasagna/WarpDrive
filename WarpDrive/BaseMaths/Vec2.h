#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <typeinfo>

template <class T>
class Vec2
{
public:
	Vec2(int = 0) : x(0), y(0) {} //the argument is to avoid a bug when making Vec2<Vec2>
	Vec2(T x, T y) : x(x), y(y) {}
	Vec2 (const Vec2<T>& ref) {this->x = ref.X(); this->y = ref.Y();}
	Vec2& operator= (const Vec2<T>& ref) {this->x = ref.X(); this->y = ref.Y(); return *this;}

	T X() const { return x; }
	T Y() const { return y; }
	void setX(T x) { this->x = x; }
	void setY(T y) { this->y = y; }

	Vec2& operator+=(const Vec2& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		return *this;
	}

	Vec2& operator-=(const Vec2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	Vec2& operator*=(T f)
	{
		x *= f;
		y *= f;
		return *this;
	}

	Vec2& operator*=(const Vec2<T>& f)
	{
		x *= f.X();
		y *= f.Y();
		return *this;
	}

	T sqMod()
	{
		T ret = (x*x)+(y*y);
		return ret;
	}

	T mod()
	{
		//TODO: Come back to this after revising templates
		T sqm = this->sqMod();
		void* p = &sqm;
		if(typeid(T) == typeid(double))
		{
		   return sqrt( *((double*) p));
		}
		if(typeid(T) == typeid(long double))
		{
		   return sqrt( *((long double*) p));
		}
		if ( ( typeid(T) == typeid(float) ) || ( typeid(T) == typeid(int) ) || ( typeid(T) == typeid(long) ) || ( typeid(T) == typeid(short) ) )
		{
		   return sqrt( *((float*) p));
		}
		else
		{
		   return 0; //sqrt will probably make no sense on this type.
		}
	}


protected:
    T x, y;
};

template <class T>
Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b)
{
    Vec2<T> res = a;
    res += b;
    return res;
}

template <class T>
Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b)
{
    Vec2<T> res = a;
    res -= b;
    return res;
}

template <class T>
Vec2<T> operator*(const Vec2<T>&a, T f)
{
    Vec2<T> res = a;
    res *= f;
    return res;
}

template <class T>
Vec2<T> operator*(const Vec2<T>&a, const Vec2<T>& b)
{
    Vec2<T> res = a;
    res *= b;
    return res;
}

template <class T>
bool operator == (const Vec2<T>&a, const Vec2<T>& b)
{
	return ( (a.X()==b.X())&&(a.Y()==b.Y()) );
}

template <class T>
bool operator != (const Vec2<T>&a, const Vec2<T>& b)
{
	return ( !(a==b) );
}

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec2d = Vec2<double>;

#endif
