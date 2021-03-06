#ifndef WD_SPRITE_HPP_DEFINED
#define WD_SPRITE_HPP_DEFINED

#include <fstream>
#include <vector>
#include <string>

#include "WarpDrive/basemaths/vec2.hpp"
#include "WarpDrive/basemaths/vec3.hpp"
#include "WarpDrive/display/animsheet.hpp"
#include "WarpDrive/basesystem/stringproc.hpp"
#include "WarpDrive/basemaths/rect.hpp"
#include "WarpDrive/basesystem/displaymanager.hpp"

class Sprite
{

public:

    Sprite(){} //Only provided for array-building purposes. This constructor will NOT provide an usable Sprite
    Sprite(const std::string& filename); // If the file is of the the type ".sheetlist", then it will be loaded as such.
                                    // If not, the constructor will understand it to be the instructions to a single
                                    // sheet and load it as a an AnimSheet loading file.

    int playAnimation(int i); //if i is already being played, next frame, else, first frame. This function updates the sprite. Returns current animation (after call)
    void draw();
    void setVel(const Vec2f& v) {vel = v;}
    void setAcc(const Vec2f& a) {accel = a;}
    void setPos(const Vec2f& p);

    const Vec2f& Velocity() const {return vel;}
    const Vec2f& Accel() const {return accel;}
    const Vec2f& Position() const {return pos;}

    void setCellTime(float secs = 0.04166f); //default = 24fps
    const Rectf& Box() const {return rect;}
    Vec2i Animation() const {return current;}
    bool pixCollision(const Sprite& other) const;
    bool pixCollision(const SDLImage& other) const;
    Rectf intersection(const Rectf& box) const; //though this should live in Rect.h, Templates make it dangerous to be there
    void setTransp(unsigned int i = 128) {transpThreshold = i;}
    void setDrawAlpha(uint8_t i);
    const AnimSheet& Sheet() const { return *sheets[static_cast<unsigned int>(animations[static_cast<unsigned int>(current.X())].first.X().X())];}
    void setColourKey(const SDLRGBColour& tc = SDLRGBColour(0,255,255));

protected:

    Vec2f vel;      //unit: Pixels/Second
    Vec2f accel;    //Speed, Acceleration and Position refer to screen movement and have nothing to do with world position
    Vec2f pos;      //All this are floats for smoothness purposes. The decimal part is cropped when drawing
    std::vector<AnimSheet*> sheets;
    Vec2i baseSize;
    Vec2i current; //(animation, frame)
    Vec2i currentCell;
    Rectf rect;
    int64_t dt;
    std::vector<std::pair< Vec3<Vec2i>, int > > animations; //{ (sheet, animation) , (startframe) , (endframe) } {animatiom to which it links to}
    int64_t maxCellTime;
    unsigned int transpThreshold; //pixels with alpha above this value count for collision;

};

#endif // WD_SPRITE_HPP_DEFINED
