#ifndef WD_CAMERA_HPP_DEFINED
#define WD_CAMERA_HPP_DEFINED

#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include <utility>

#include "WarpDrive/basemaths/vec3.hpp"
#include "WarpDrive/basemaths/ray.hpp"
#include "WarpDrive/basesystem/gameobject.hpp"

class Camera: public GameObject
{
public:

    Camera();
    void update() override;
    void draw() const override;
    void use() const;

    void setTarget(const Vec3f& targetPos);
    void setTarget(const GameObject* targetObject);
    std::pair<bool, Vec3f> Target() const;
    void setRelativePos(const Vec3f& Relative); //Relative Position to a targeted Object
    Vec3f RelativePos() const {return relativePos;}

    Ray traceRay(int x, int y) const noexcept;

    //orbits around a target object (if any). X, Y and Z are the factors by which the camera moves in each axis
    void orbit(float X, float Y, float Z, float radius, float periodSecs = 1);

    //TODO: Function currently broken in some situations. Must be fixed and given new signature where XYZ represent an axis

private:

    Vec3f up;
    const GameObject* targetObj;
    Vec3f target;
    Vec3f relativePos;
    Vec3f orbitFactors;
    float orbitRadius;
    float orbitPeriod;
    float time;

};

#endif //WD_CAMERA_HPP_DEFINED
