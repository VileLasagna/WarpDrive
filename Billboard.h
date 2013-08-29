#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "Vec3.h"


class Billboard
{
public:
	Billboard(float Size = 1, Vec3f Pos = Vec3f(), bool absoluteUp = false){ size = Size; pos = Pos; absUp = absoluteUp;}
	void Draw() const;
	void setPos(Vec3f P) {pos = P;}
	void usingAbsoluteUp(bool b = true) {absUp = true;}

private:

	float size;
	Vec3f pos;
	bool absUp;

};






#endif //BILLBOARD_H