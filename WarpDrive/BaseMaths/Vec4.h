#ifndef VEC4_H
#define VEC4_H

#include "Vec2.h"
#include "Vec3.h"


template <class T>
class Vec4
{
public:

	Vec4() : x(0), y(0), z(0), w(1) {}
    Vec4(T x, T y, T z, T w) {this->x = x; this->y = y; this->z = z; this->w = w;}
	Vec4 (const Vec2<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = 0; this->w = 1}
	Vec4 (const Vec3<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = ref.Z(); this->w = 1;}
	Vec4& operator= (const Vec4<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = ref.Z(); this->w = ref.W(); return *this;}

	T X() const { return x; }
    T Y() const { return y; }
	T Z() const { return z; }
	T W() const { return w; }
    void setX(T x) { this->x = x; }
    void setY(T y) { this->y = y; }
	void setZ(T z) { this->z = z; }
	void setW(T w) { this->w = w; }

	Vec4 operator+=(const Vec4& rhs)
    {
		if (this->w == rhs.W())
		{
			this->x += rhs.x;
			this->y += rhs.y;
			this->z += rhs.z;
		}
		else
		{
			this->x += (rhs.x/rhs.w)*this->w;
			this->y += (rhs.y/rhs.w)*this->w;
			this->z += (rhs.z/rhs.w)*this->w;
		}
        return *this;
    }

	Vec4& operator*=(const T& f)
    {
        this->x *= f;
        this->y *= f;
		this->z *= f;
        return *this;
    }


	T sqMod() const
	{
		if (w == 1)
		{
			return x*x+y*y+z*z;
		}
		else
		{
			return (x/w)*(x/w) + (y/w)*(y/w) + (z/w)*(z/w);
		}
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
		x /= m*w;
		y /= m*w;
		z /= m*w;
	}

	Vec3<T> toVec3()
	{
		if (w == 1)
		{
			return Vec3<T>(x,y,z);
		}
		else
		{
			return Vec3<T>(x/w,y/w,z/w);
		}
	}


protected:

	T x;
	T y;
	T z;
	T w;

};

template <class T>
Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b)
{
    Vec4<T> res = a;
    res += b;
    return res;
}

template <class T>
Vec4<T> operator*(const Vec4<T>&a, T f)
{
    Vec4<T> res = a;
    res *= f;
    return res;
}

template <class T>
bool operator == (const Vec4<T>&a, const Vec4<T>& b)
{
	if ( a.W() == b.W())
	{
		return ( (a.X()==b.X())&&(a.Y()==b.Y())&&(a.Z()==b.Z()));
	}
	else
	{
		return ( ((a.X()/a.W())==(b.X()/b.W()))&&((a.Y()/a.W())==(b.Y()/b.W()))&&((a.Z()/a.W())==(b.Z()/b.W())));
	}
}

template <class T>
bool operator != (const Vec4<T>&a, const Vec4<T>& b)
{
	return !(a==b);
}

template <class T>
Vec4<T> operator- (const Vec4<T>& v)
{
	Vec4<T> ret(-(v.X()), -(v.Y()), -(v.Z()), V.W());
	return ret;
}

template <class T>

Vec4<T> operator- (const Vec4<T>& a, const Vec4<T>& b)
{
	Vec4<T> ret;
	if( a.W() == b.W())
	{
		ret = Vec4<T>(a.X() - b.X(), a.Y()-b.Y(), a.Z() - b.Z(), a.W());
	}
	else
	{
		ret = Vec4<T>(a.X()/a.W() - b.X()/b.W(), a.Y()/a.W()-b.Y()/b.W(), a.Z()/a.W() - b.Z()/b.W(), 1);
	}
	return ret;
}

template <class T>
Vec4<T> crossProd (const Vec4<T>& a, const Vec4<T>& b)
{
	Vec4<T> ret;
	if (a.W() == b.W())
	{
		ret = Vec4<T>(a.Y()*b.Z() - a.Z()*b.Y(), a.Z()*b.X() - a.X()*b.Z(), a.X()*b.Y() - a.Y()*b.X(), a.W());
	}
	else
	{
		ret = Vec4<T>((a.Y()/a.W())*(b.Z()/b.W()) - (a.Z()/a.W())*(b.Y()/b.W()),
						(a.Z()/a.W())*(b.X()/b.W()) - (a.X()/a.W())*(b.Z()/b.W()),
						(a.X()/a.W())*(b.Y()/b.W()) - (a.Y()/a.W())*(b.X()/b.W()),
						a.W());
	}
	return ret;
}

template <class T>
T dotProd (const Vec4<T>& a, const Vec4<T>& b)
{
	if(a.W() == b.W())
	{
		return a.X()*b.X() + a.Y()*b.Y() + a.Z()*b.Z();
	}
	else
	{
		return (a.X()/a.W())*(b.X()/b.W()) + (a.Y()/a.W())*(b.Y()/b.W()) + (a.Z()/a.W())*(b.Z()/b.W());
	}
}

template <class T>
Vec4<T> triNormal(const Vec4<T>& v1, const Vec4<T>& v2, const Vec4<T>& v3)
{
	Vec3<T>[3] v = {v1.toVec3(), v2.toVec3(), v3.toVec3()};

	return Vec4<T>(triNormal(v));
}

template <class T>
Vec4<T> triNormal(const Vec4<T>* v)
{
	return triNormal(v[0],v[1],v[2]);
}
typedef Vec4<float> Vec4f;
typedef Vec4<int> Vec4i;
typedef Vec4<double> Vec4d;


#endif //VEC3_H