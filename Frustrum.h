#ifndef FRUSTRUM_H_DEFINED
#define FRUSTRUM_H_DEFINED


#include "Matrix44.h"
#include "BoundingBox.h"

class Frustrum
{
public:

	Frustrum();
	void Update();
	bool isInside(const Vec4f& v);
	bool intersects(const BBox& Box);

private:


	Matrix44 ClipMatrix;



};

#endif //FRUSTRUM_H_DEFINED