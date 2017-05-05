#include "WarpDrive/basemaths/capsule.hpp"

bool Capsule::Collides(const Sphere &S) const
{
	return path.sqDistToPoint(S.Centre()) <= (R+S.Radius())*(R+S.Radius());
}

Capsule::Capsule() noexcept:
	path{LineSeg()},
	R{0} {}

Capsule::Capsule(const LineSeg& p, float r) noexcept
{
    path = {p};
	R = {r};
}

Capsule::Capsule(const Vec3f &A, const Vec3f &B, float r) noexcept
{
	path = {LineSeg(A,B)};
	R = {r};
}

Capsule::Capsule(const Sphere &S, const Vec3f &Path) noexcept
{
	this->path = LineSeg(S.Centre(), S.Centre()+Path);
	R = S.Radius();
}
