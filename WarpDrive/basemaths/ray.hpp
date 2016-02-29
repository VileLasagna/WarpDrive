#ifndef RAY_HPP_DEFINED
#define RAY_HPP_DEFINED

#include "basemaths/vec3.hpp"
#include "basemaths/lineseg.hpp"


class Ray
{

public:

    Ray(Vec3f o = Vec3f(0,0,0) , Vec3f d = Vec3f(0,0,1)) : origin{o}, direction{d.normalise()} {}
    Ray(LineSeg segment) : origin{segment.getStart()}, direction{(segment.getEnd() - segment.getStart()).normalise()} {}

    Vec3f Origin() const noexcept {return origin;}
    Vec3f Direction() const noexcept {return direction;}

    void setOrigin(Vec3f& newOrigin) noexcept {origin = newOrigin;}
    void setOrigin(Vec3f&& newOrigin) noexcept {origin = newOrigin;}

    void setDirection(Vec3f& newDirection) noexcept {direction = newDirection;}
    void setDirection(Vec3f&& newDirection) noexcept {direction = newDirection;}

    LineSeg getSegment(float start, float end) const noexcept;

    Vec3f pointAt(float distance) const noexcept;

private:

    Vec3f origin;
    Vec3f direction;

};

#endif // RAY_HPP_DEFINED
