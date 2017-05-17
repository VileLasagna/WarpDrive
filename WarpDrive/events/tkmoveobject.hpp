#ifndef WD_TK_MOVE_OBJECT_HPP_DEFINED
#define WD_TK_MOVE_OBJECT_HPP_DEFINED

#include <string>

#include "WarpDrive/events/timelinekey.hpp"
#include "WarpDrive/basemaths/vec3.hpp"

class TKMoveObject: public TimelineKey
{
public:

    TKMoveObject
        (float Time = -0.01f , //by default it comes right after the last added key
        std::string ObjName = "", //The name or Type of the object/objects you want to influence
        bool UniqueID = true, //if this is true you are referring to a single object, else you want to alter all objects of a specific type
        bool ChangePos = false,
        bool ChangeVel = false,
        bool ChangeAccel = false,
        const Vec3f& Pos = Vec3f(0,0,0),
        const Vec3f& Vel= Vec3f(0,0,0),
        const Vec3f& Accel= Vec3f(0,0,0));

    void trigger();

protected:

    Vec3f pos,vel,acc;
    Vec3<bool> changes;
    std::string name;
    bool isUnique;

};

#endif //WD_TK_MOVE_OBJECT_HPP_DEFINED
