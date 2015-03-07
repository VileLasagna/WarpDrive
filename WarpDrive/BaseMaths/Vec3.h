#ifndef VEC3_H
#define VEC3_H

#include "BaseMaths/Vec2.h"


template <class T>
class Vec3
{
public:

	Vec3() : x(0), y(0), z(0) {}
	Vec3(T x, T y, T z) {this->x = x; this->y = y; this->z = z;}
	Vec3 (const Vec2<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = 0;}
	Vec3 (const Vec3<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = ref.Z();}
	Vec3& operator= (const Vec3<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = ref.Z(); return *this;}

	T X() const { return x; }
	T Y() const { return y; }
	T Z() const { return z; }
	void setX(T x) { this->x = x; }
	void setY(T y) { this->y = y; }
	void setZ(T z) { this->z = z; }

    T R() const { return x; }
    T G() const { return y; }
    T B() const { return z; }
    void setR(T x) { this->x = x; }
    void setG(T y) { this->y = y; }
    void setB(T z) { this->z = z; }

	Vec3& operator+=(const Vec3& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		this->z += rhs.z;
		return *this;
	}

	Vec3& operator*=(const T& f)
	{
		this->x *= f;
		this->y *= f;
		this->z *= f;
		return *this;
	}
	Vec3& operator/=(const T& f)
	{
		this->x /= f;
		this->y /= f;
		this->z /= f;
		return *this;
	}
    Vec3& operator*=(const Vec3<T>& f)
    {
        this->x *= f.X();
        this->y *= f.Y();
		this->z *= f.Z();
        return *this;
    }

	T sqMod() const
	{
		return x*x+y*y+z*z;
	}

	T mod() const
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

	void normalise()
	{
		T m = this->mod();
		x /= m;
		y /= m;
		z /= m;
	}


protected:

	T x;
	T y;
	T z;

};

template <class T>
Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b)
{
    Vec3<T> res = a;
    res += b;
    return res;
}

template <class T>
Vec3<T> operator*(const Vec3<T>&a, T f)
{
    Vec3<T> res = a;
    res *= f;
    return res;
}

template <class T>
Vec3<T> operator/(const Vec3<T>&a, T f)
{
    Vec3<T> res = a;
    res /= f;
    return res;
}

template <class T>
bool operator == (const Vec3<T>&a, const Vec3<T>& b)
{
	return ( (a.X()==b.X())&&(a.Y()==b.Y())&&(a.Z()==b.Z()));
}

template <class T>
bool operator != (const Vec3<T>&a, const Vec3<T>& b)
{
	return !(a==b);
}

template <class T>
Vec3<T> operator- (const Vec3<T>& v)
{
	Vec3<T> ret(-(v.X()), -(v.Y()), -(v.Z()));
	return ret;
}

template <class T>

Vec3<T> operator- (const Vec3<T>& a, const Vec3<T>& b)
{
	Vec3<T> ret(a.X() - b.X(), a.Y()-b.Y(), a.Z() - b.Z());
	return ret;
}

template <class T>
static Vec3<T> crossProd (const Vec3<T>& a, const Vec3<T>& b)
{
	Vec3<T> ret(a.Y()*b.Z() - a.Z()*b.Y(), a.Z()*b.X() - a.X()*b.Z(), a.X()*b.Y() - a.Y()*b.X());
	return ret;
}

template <class T>
static T dotProd (const Vec3<T>& a, const Vec3<T>& b)
{
	return a.X()*b.X() + a.Y()*b.Y() + a.Z()*b.Z();
}

template <class T>
static Vec3<T> triNormal(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c)
{
	//TODO: winding checks and tuning.
	//ALSO: I feel this is not the best place for this to be so it's kind of temporary for now
	Vec3<T> ab = b-a;
	Vec3<T> ac = c-a;
	
	Vec3<T> normal = crossProd(ab, ac);
	normal.normalise();
	return normal;
}


template <class T>
static Vec3<T> triNormal(const Vec3<T>* v)
{
	return triNormal(v[0],v[1],v[2]);
}

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;
using Vec3d = Vec3<double>;



#endif //VEC3_H
