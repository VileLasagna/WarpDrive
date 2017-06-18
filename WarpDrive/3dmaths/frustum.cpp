#include "WarpDrive/3dmaths/frustum.hpp"



void Frustum::update() noexcept
{
    Matrix44 MV;
    Matrix44 Proj;

    MV.getModelview();
    Proj.getProjection();

    MV.multiply(Proj);

    clipMatrix = MV;

}

bool Frustum::isInside(const Vec4f& v) const noexcept
{
    Vec4f V = Matrix44::multiply(clipMatrix,v);

    float w = V.W();
    return  (V.X() >= (-w)) &&
            (V.X() <= w)    &&
            (V.Y() >= (-w)) &&
            (V.Y() <= w)    &&
            (V.Z() >= (-w)) &&
            (V.Z() <= w);
}

bool Frustum::intersects(const AABBox& ) const
{

#pragma message "TODO - Missing implementation"

    return false;

}
