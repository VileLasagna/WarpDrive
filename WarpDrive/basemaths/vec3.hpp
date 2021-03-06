#ifndef WD_VEC3_HPP_DEFINED
#define WD_VEC3_HPP_DEFINED

#include "WarpDrive/basemaths/vec2.hpp"
#include "WarpDrive/basesystem/util.hpp"


template <typename T>
class Vec3
{
public:

    constexpr explicit Vec3() : x(0), y(0), z(0) {}
    constexpr explicit Vec3(T xVal, T yVal, T zVal): x{xVal}, y{yVal}, z{zVal} {}
    constexpr explicit Vec3 (const Vec2<T>& ref): x{ref.X()}, y{ref.Y()}, z{0} {}
    constexpr Vec3 (const Vec3<T>& ref): x{ref.X()}, y{ref.Y()}, z{ref.Z()} {}
    Vec3& operator= (const Vec3<T>& ref) {this->x = ref.X(); this->y = ref.Y(); this->z = ref.Z(); return *this;}

    constexpr T X() const { return x; }
    constexpr T Y() const { return y; }
    constexpr T Z() const { return z; }
    constexpr void setX(T newX) { x = newX; }
    constexpr void setY(T newY) { y = newY; }
    constexpr void setZ(T newZ) { z = newZ; }

    constexpr T R() const { return x; }
    constexpr T G() const { return y; }
    constexpr T B() const { return z; }
    constexpr void setR(T r) { x = r; }
    constexpr void setG(T g) { y = g; }
    constexpr void setB(T b) { z = b; }

    constexpr Vec3& operator+=(const Vec3& rhs)
    {
        this->x += rhs.x;
        this->y += rhs.y;
        this->z += rhs.z;
        return *this;
    }

    constexpr Vec3& operator*=(const T& f)
    {
        x *= f;
        y *= f;
        z *= f;
        return *this;
    }
    constexpr Vec3& operator/=(const T& f)
    {
        x /= f;
        y /= f;
        z /= f;
        return *this;
    }
    constexpr Vec3& operator*=(const Vec3<T>& rhs)
    {
        x *= rhs.X();
        y *= rhs.Y();
        z *= rhs.Z();
        return *this;
    }

    constexpr T sqMod() const
    {
        return x*x+y*y+z*z;
    }

    T mod()
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-conversion"
#pragma clang diagnostic ignored "-Wconversion"

        return sqrt(sqMod());

#pragma clang diagnostic pop
    }

    Vec3<T>& normalise()
    {
        T m = this->mod();
        x /= m;
        y /= m;
        z /= m;

        return *this;
    }


protected:

    T x;
    T y;
    T z;

};

template <typename T>
constexpr Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b)
{
    Vec3<T> res = a;
    res += b;
    return res;
}

template <typename T>
constexpr Vec3<T> operator*(const Vec3<T>&a, T f)
{
    Vec3<T> res = a;
    res *= f;
    return res;
}

template <typename T>
constexpr Vec3<T> operator/(const Vec3<T>&a, T f)
{
    Vec3<T> res = a;
    res /= f;
    return res;
}

template <typename T>
constexpr bool operator == (const Vec3<T>&a, const Vec3<T>& b)
{
    return ( WrpDrv::flEquals(a.X(),b.X()) &&
             WrpDrv::flEquals(a.Y(),b.Y()) &&
             WrpDrv::flEquals(a.Z(),b.Z()) );
}

template <typename T>
constexpr bool operator != (const Vec3<T>&a, const Vec3<T>& b)
{
    return !(a==b);
}

template <typename T>
constexpr Vec3<T> operator- (const Vec3<T>& v)
{
    Vec3<T> ret( -(v.X()), -(v.Y()), -(v.Z()) );
    return ret;
}

template <typename T>
constexpr Vec3<T> operator- (const Vec3<T>& a, const Vec3<T>& b)
{
    return Vec3<T>(a.X() - b.X(), a.Y()-b.Y(), a.Z() - b.Z());
}

template <typename T>
constexpr static Vec3<T> crossProd (const Vec3<T>& a, const Vec3<T>& b)
{
    return Vec3<T>(a.Y()*b.Z() - a.Z()*b.Y(), a.Z()*b.X() - a.X()*b.Z(), a.X()*b.Y() - a.Y()*b.X());
}

template <typename T>
constexpr static T dotProd (const Vec3<T>& a, const Vec3<T>& b)
{
    return a.X()*b.X() + a.Y()*b.Y() + a.Z()*b.Z();
}

template <typename T>
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


template <typename T>
static Vec3<T> triNormal(const Vec3<T>* v)
{
    return triNormal(v[0],v[1],v[2]);
}

using Vec3f = Vec3<float>;
using Vec3i = Vec3<int>;
using Vec3d = Vec3<double>;

#endif //WD_VEC3_HPP_DEFINED
