#ifndef FRUSTRUM_H_DEFINED
#define FRUSTRUM_H_DEFINED


#include "BaseMaths/Matrix44.h"
#include "Physics/BoundingBox.h"

class Frustrum
{
public:

	Frustrum() = default;
	void Update();
	bool isInside(const Vec4f& v) const;
	bool intersects(const BBox& Box) const;

private:


	Matrix44 ClipMatrix;



};

#endif //FRUSTRUM_H_DEFINED
