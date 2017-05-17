#ifndef WD_CAPSULE_SHAPE_HPP_DEFINED
#define WD_CAPSULE_SHAPE_HPP_DEFINED

#include "WarpDrive/basemaths/sphere.hpp"
#include "WarpDrive/basemaths/lineseg.hpp"
#include "WarpDrive/basemaths/vec3.hpp"


class Capsule
{
public:

    Capsule() noexcept;
    Capsule(const LineSeg& path, float r) noexcept;
    Capsule(const Vec3f& A, const Vec3f& B, float r) noexcept;
    Capsule(const Sphere& S, const Vec3f& path) noexcept;

    bool Collides( const Sphere& S) const;
    bool Collides( const Capsule& C) const;
    float Radius() const noexcept {return R;}
    LineSeg Path()const noexcept {return path;}


private:

    LineSeg path;
    float R;

};

#endif //WD_CAPSULE_SHAPE_HPP_DEFINED
