#ifndef CAPSULE_SHAPE_H
#define CAPSULE_SHAPE_H

#include "BaseMaths/Sphere.hpp"
#include "BaseMaths/LineSeg.hpp"
#include "BaseMaths/Vec3.hpp"


class Capsule
{
public:

	Capsule();
	Capsule(const LineSeg& path, float r);
	Capsule(const Vec3f& A, const Vec3f& B, float r);
	Capsule(const Sphere& S, const Vec3f& Path);

	bool Collides( const Sphere& S) const;
	bool Collides( const Capsule& C) const;
	float radius() const {return R;}
	LineSeg getPath()const {return Path;}


private:

	LineSeg Path;
	float R;

};

#endif //CAPSULE_SHAPE_H
