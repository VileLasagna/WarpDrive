#include "BaseMaths/Capsule.hpp"

bool Capsule::Collides(const Sphere &S) const
{
	return Path.sqDistToPoint(S.getCentre()) <= (R+S.getRadius())*(R+S.getRadius());
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
	this->Path = LineSeg(S.getCentre(), S.getCentre()+Path);
	R = S.getRadius();
}
