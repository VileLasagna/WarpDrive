#ifndef WD_FRUSTRUM_HPP_DEFINED
#define WD_FRUSTRUM_HPP_DEFINED


#include "basemaths/matrix44.hpp"
#include "physics/alignedboundingbox.hpp"

class Frustrum
{
public:

    Frustrum() = default;
    void update() noexcept;
    bool isInside(const Vec4f& v) const noexcept;
    bool intersects(const AABBox& Box) const;

private:


    Matrix44 clipMatrix;



};

#endif //WD_FRUSTRUM_HPP_DEFINED
