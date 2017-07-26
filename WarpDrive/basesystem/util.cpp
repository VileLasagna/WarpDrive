#include "WarpDrive/basesystem/util.hpp"

#include <cmath>

namespace WrpDrv
{

    bool flEquals(float f1, float f2)
    {
        return( fabs(static_cast<double>(f1 - f2)) <= WrpDrv::flEpsilon);
    }
    bool dbEquals(double f1, double f2)
    {
        return( fabs(f1 - f2) <= WrpDrv::flEpsilon);
    }

    bool flZero(float f)
    {
        return( fabs(static_cast<double>(f)) <= WrpDrv::flEpsilon);
    }
    bool dbZero(double f)
    {
        return( fabs(f) <= WrpDrv::flEpsilon);
    }
}
