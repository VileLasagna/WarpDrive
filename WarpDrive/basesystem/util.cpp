#include "WarpDrive/basesystem/util.hpp"

#include <cmath>

namespace WrpDrv
{

    bool flEquals(double f1, double f2)
    {
        return( (fabs(f1) - fabs(f2)) <= WrpDrv::flEpsilon);
    }

}
