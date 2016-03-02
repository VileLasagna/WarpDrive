#include "basemaths/capsule.hpp"

bool Capsule::Collides(const Sphere &S) const
{
	return Path.sqDistToPoint(S.Centre()) <= (R+S.Radius())*(R+S.Radius());
}

Capsule::Capsule():
	Path{LineSeg()},
	R{0} {}

Capsule::Capsule(const LineSeg& path, float r)
{
	Path = {path};
	R = {r};
}

Capsule::Capsule(const Vec3f &A, const Vec3f &B, float r)
{
	Path = {LineSeg(A,B)};
	R = {r};
}

Capsule::Capsule(const Sphere &S, const Vec3f &Path)
{
	this->Path = LineSeg(S.Centre(), S.Centre()+Path);
	R = S.Radius();
}
