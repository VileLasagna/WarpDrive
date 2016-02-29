#include "basemaths/frustrum.hpp"



void Frustrum::Update()
{
	Matrix44 MV;
	Matrix44 Proj;

	MV.getModelview();
	Proj.getProjection();

	MV.Multiply(Proj);

	ClipMatrix = MV;

}

bool Frustrum::isInside(const Vec4f& v) const
{
	Vec4f V = Matrix44::Multiply(ClipMatrix,v);

	float w = V.W();
	return	(V.X() >= (-w)) &&
			(V.X() <= w)    &&
			(V.Y() >= (-w)) &&
			(V.Y() <= w)    &&
			(V.Z() >= (-w)) &&
			(V.Z() <= w);
}

bool Frustrum::intersects(const AABBox& ) const
{

#pragma message "TODO - Missing implementation"

	return false;

}
