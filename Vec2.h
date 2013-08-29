#ifndef VEC2_H
#define VEC2_H

#include <cmath>
#include <typeinfo>

template <class T>
class Vec2
{
public:
    Vec2(int i = 0) : x(0), y(0) {} //the argument is to avoid a bug when making Vec2<Vec2> 
    Vec2(T x, T y) : x(x), y(y) {}
	Vec2 (const Vec2<T>& ref) {this->x = ref.X(); this->y = ref.Y();}
	Vec2& operator= (const Vec2<T>& ref) {this->x = ref.X(); this->y = ref.Y(); return *this;}

    T X() const { return x; }
    T Y() const { return y; }
    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }

   Vec2& operator+=(const Vec2& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        return *this;
    }
      Vec2& operator-=(const Vec2& rhs)
    {
        this->x -= rhs.x;
        this->y -= rhs.y;
        return *this;
    }

   Vec2& operator*=(T f)
    {
        this->x *= f;
        this->y *= f;
        return *this;
    }

   Vec2& operator*=(const Vec2<T>& f)
    {
        this->x *= f.X();
        this->y *= f.Y();
        return *this;
    }

   T sqMod()
   {
	   T ret = ((this->x)*(this->x))+((this->y)*(this->y)) ;
	   return ret;
   }

   T mod()
   {
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

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec2<double> Vec2d;

#endif