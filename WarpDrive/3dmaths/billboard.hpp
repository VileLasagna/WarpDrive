#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "basemaths/vec3.hpp"


class Billboard
{

public:

    Billboard(float Size = 1, Vec3f Pos = Vec3f(), bool absoluteUp = false) noexcept { size = Size; pos = Pos; absUp = absoluteUp;}
	void Draw() const;
    void setPos(Vec3f P) noexcept {pos = P;}
    void usingAbsoluteUp(bool b = true) {absUp = b;}
    Vec3f Position() const noexcept { return pos;}

private:

	float size;
	Vec3f pos;
	bool absUp;

};

#endif //BILLBOARD_H
