#ifndef WD_BILLBOARD_HPP_DEFINED
#define WD_BILLBOARD_HPP_DEFINED

#include "WarpDrive/basemaths/vec3.hpp"


class Billboard
{

public:

    Billboard(float Size = 1, Vec3f Pos = Vec3f(), bool absoluteUp = false) noexcept { size = Size; pos = Pos; absUp = absoluteUp;}
    void draw() const;
    void setPos(Vec3f P) noexcept {pos = P;}
    void usingAbsoluteUp(bool b = true) {absUp = b;}
    Vec3f Position() const noexcept { return pos;}

private:

    float size;
    Vec3f pos;
    bool absUp;

};

#endif //WD_BILLBOARD_HPP_DEFINED
