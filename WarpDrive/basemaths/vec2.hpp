#ifndef WD_VEC2_HPP_DEFINED
#define WD_VEC2_HPP_DEFINED

#include <cmath>
#include <type_traits>

template <typename T>
class Vec2
{
public:
    constexpr explicit Vec2(int = 0) : x(0), y(0) {} //the argument is to avoid a bug when making Vec2<Vec2>
    constexpr explicit Vec2(T xVal, T yVal) : x(xVal), y(yVal) {}
    constexpr Vec2(const Vec2<T>& ref): x{ref.X()}, y{ref.Y()} {}
    constexpr Vec2& operator= (const Vec2<T>& ref){ x = ref.X(); y = ref.Y(); return *this;}

    constexpr T X() const { return x; }
    constexpr T Y() const { return y; }
    constexpr void setX(T newX) { x = newX; }
    constexpr void setY(T newY) { y = newY; }

    constexpr Vec2& operator+=(const Vec2& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    constexpr Vec2& operator-=(const Vec2& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    constexpr Vec2& operator*=(T f)
    {
        x *= f;
        y *= f;
        return *this;
    }

    constexpr Vec2& operator*=(const Vec2<T>& f)
    {
        x *= f.X();
        y *= f.Y();
        return *this;
    }

    constexpr T sqMod()
    {
        return (x*x)+(y*y);
    }

//    typename std::enable_if<std::is_arithmetic<T>::value, double>::type mod()
//    {
//        return sqrt(sqMod());
//    }

//    typename std::enable_if<!(std::is_arithmetic<T>::value), double>::type mod()
//    {
//        return sqrt(0);
//    }

    T mod()
    {

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-conversion"
#pragma clang diagnostic ignored "-Wconversion"

        return sqrt(sqMod());

#pragma clang diagnostic pop

    }

protected:
    T x, y;
};


//template<typename T>
//typename std::enable_if<std::is_arithmetic<T>::value, double>::type Vec2<T>::mod()
//{
//    return sqrt(sqMod());
//}

template <typename T>
constexpr Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b)
{
    Vec2<T> res = a;
    res += b;
    return res;
}

template <typename T>
constexpr Vec2<T> operator-(const Vec2<T>& a, const Vec2<T>& b)
{
    Vec2<T> res = a;
    res -= b;
    return res;
}

template <typename T>
constexpr Vec2<T> operator*(const Vec2<T>&a, T f)
{
    Vec2<T> res = a;
    res *= f;
    return res;
}

template <typename T>
constexpr Vec2<T> operator*(const Vec2<T>&a, const Vec2<T>& b)
{
    Vec2<T> res = a;
    res *= b;
    return res;
}

template <typename T>
constexpr bool operator == (const Vec2<T>&a, const Vec2<T>& b)
{
    return ( (a.X()==b.X())&&(a.Y()==b.Y()) );
}

template <typename T>
constexpr bool operator != (const Vec2<T>&a, const Vec2<T>& b)
{
    return ( !(a==b) );
}

using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
using Vec2d = Vec2<double>;

#endif //WD_VEC2_HPP_DEFINED
