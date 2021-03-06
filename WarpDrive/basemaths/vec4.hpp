#ifndef WD_VEC4_HPP_DEFINED
#define WD_VEC4_HPP_DEFINED

#include "WarpDrive/basemaths/vec2.hpp"
#include "WarpDrive/basemaths/vec3.hpp"


template <typename T>
class Vec4
{
public:

    constexpr Vec4() : x(0), y(0), z(0), w(1) {}
    constexpr Vec4(T xVal, T yVal, T zVal, T wVal): x{xVal}, y{yVal}, z{zVal}, w{wVal} {}
    constexpr Vec4 (const Vec2<T>& ref): x{ref.X()}, y{ref.Y()}, z{0}, w{1} {}
    constexpr Vec4 (const Vec3<T>& ref): x{ref.X()}, y{ref.Y()}, z{ref.Z()}, w{1} {}
    //constexpr Vec4& operator= (const Vec4<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = ref.Z(); this->w = ref.W(); return *this;}

    constexpr T X() const { return x; }
    constexpr T Y() const { return y; }
    constexpr T Z() const { return z; }
    constexpr T W() const { return w; }
    constexpr void setX(T newX) { x = newX; }
    constexpr void setY(T newY) { y = newY; }
    constexpr void setZ(T newZ) { z = newZ; }
    constexpr void setW(T newW) { w = newW; }

    constexpr Vec4& operator+=(const Vec4& rhs)
    {
        if (w == rhs.W())
        {
            x += rhs.X();
            y += rhs.Y();
            z += rhs.Z();
        }
        else
        {
            x += (rhs.X()/rhs.W())*w;
            y += (rhs.Y()/rhs.W())*w;
            z += (rhs.Z()/rhs.W())*w;
        }
        return *this;
    }

    constexpr Vec4& operator*=(const T& f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }


    constexpr T sqMod() const
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

    T mod()
    {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-conversion"
#pragma clang diagnostic ignored "-Wconversion"

        return sqrt(sqMod());

#pragma clang diagnostic pop

    }

    void normalise()
    {
        T m = mod();
        x /= m*w;
        y /= m*w;
        z /= m*w;
    }

    constexpr Vec3<T> toVec3()
    {
        if (WrpDrv::flEquals(w, 1))
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

template <typename T>
constexpr Vec4<T> operator+(const Vec4<T>& a, const Vec4<T>& b)
{
    Vec4<T> res = a;
    res += b;
    return res;
}

template <typename T>
constexpr Vec4<T> operator*(const Vec4<T>&a, T f)
{
    Vec4<T> res = a;
    res *= f;
    return res;
}

template <typename T>
constexpr bool operator == (const Vec4<T>&a, const Vec4<T>& b)
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

template <typename T>
constexpr bool operator != (const Vec4<T>&a, const Vec4<T>& b)
{
    return !(a==b);
}

template <typename T>
constexpr Vec4<T> operator- (const Vec4<T>& v)
{
    Vec4<T> ret(-(v.X()), -(v.Y()), -(v.Z()), v.W());
    return ret;
}

template <typename T>
constexpr Vec4<T> operator- (const Vec4<T>& a, const Vec4<T>& b)
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

template <typename T>
constexpr Vec4<T> crossProd (const Vec4<T>& a, const Vec4<T>& b)
{
    Vec4<T> ret;
    if (a.W() == b.W())
    {
        ret = Vec4<T>(a.Y()*b.Z() - a.Z()*b.Y(), a.Z()*b.X() - a.X()*b.Z(), a.X()*b.Y() - a.Y()*b.X(), a.W());
    }
    else
    {
        ret = Vec4<T>(  (a.Y()/a.W())*(b.Z()/b.W()) - (a.Z()/a.W())*(b.Y()/b.W()),
                        (a.Z()/a.W())*(b.X()/b.W()) - (a.X()/a.W())*(b.Z()/b.W()),
                        (a.X()/a.W())*(b.Y()/b.W()) - (a.Y()/a.W())*(b.X()/b.W()),
                        a.W());
    }
    return ret;
}

template <typename T>
constexpr T dotProd (const Vec4<T>& a, const Vec4<T>& b)
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

template <typename T>
Vec4<T> triNormal(const Vec4<T>& v1, const Vec4<T>& v2, const Vec4<T>& v3)
{
    Vec3<T> v [3] = {v1.toVec3(), v2.toVec3(), v3.toVec3()};

    return Vec4<T>(triNormal(v));
}

template <typename T>
Vec4<T> triNormal(const Vec4<T>* v)
{
    return Vec3<T>::triNormal(v[0],v[1],v[2]);
}

using Vec4f = Vec4<float>;
using Vec4i = Vec4<int>;
using Vec4d = Vec4<double>;

#endif //WD_VEC4_HPP_DEFINED
