#ifndef WD_UTIL_HPP_DEFINED
#define WD_UTIL_HPP_DEFINED


namespace WrpDrv
{
    constexpr double flEpsilon = 0.00001;

    bool flEquals(float f1, float f2);
    bool dbEquals(double f1, double f2);

    bool flZero(float f);
    bool dbZero(double f);
}

#endif // WD_UTIL_HPP_DEFINED
