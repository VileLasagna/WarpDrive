#include "WarpDrive/basemaths/ray.hpp"


LineSeg Ray::getSegment(float start, float end) const noexcept
{
    return LineSeg(pointAt(start), pointAt(end));
}

Vec3f Ray::pointAt(float distance) const noexcept
{
    return Vec3f{origin + (direction*distance)};
}
