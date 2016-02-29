#ifndef FRUSTRUM_H_DEFINED
#define FRUSTRUM_H_DEFINED


#include "basemaths/matrix44.hpp"
#include "physics/alignedboundingbox.hpp"

class Frustrum
{
public:

	Frustrum() = default;
	void Update();
	bool isInside(const Vec4f& v) const;
    bool intersects(const AABBox& Box) const;

private:


	Matrix44 ClipMatrix;



};

#endif //FRUSTRUM_H_DEFINED
