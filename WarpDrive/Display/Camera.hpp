
#ifndef CAMERA_H
#define CAMERA_H

#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include "BaseMaths/Vec3.hpp"
#include "BaseMaths/ray.hpp"
#include "BaseSystem/GameObject.hpp"
#include <utility>
#include <GL/gl.h>

class Camera: public GameObject
{
public:

	Camera();
	void Update();
	void Draw();
	void Use();

	void setTarget(const Vec3f& targetPos);
	void setTarget(const GameObject* targetObject);
	std::pair<bool, Vec3f> getTarget() const;
	void setRelativePos(const Vec3f& Relative); //Relative Position to a targeted Object
	Vec3f getRelativePos() const {return relativePos;}

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

#endif //CAMERA_H
