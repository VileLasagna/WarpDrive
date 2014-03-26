#include "Display/Camera.h"
#include "BaseMaths/Sphere.h"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <GL/glut.h>


Camera::Camera()
{
	targetObj = 0;
	up = Vec3f(0,1,0);
	type = "Camera";
	removeMe = false;
}

void Camera::Update()
{

	GameObject::Update();
	if(targetObj)
	{
		target = targetObj->getPos();
		pos = target + relativePos;
	}
	else
	{
	/*	vel += accel*DisplayManager::instance()->getDtSecs();
		pos += vel*DisplayManager::instance()->getDtSecs();*/
	}
}

void Camera::setTarget(const Vec3f& targetPos)
{
	target = targetPos;
}

void Camera::setTarget(const GameObject *targetObject)
{
	targetObj = targetObject;
}

void Camera::setRelativePos(const Vec3f &Relative)
{
	relativePos = Relative;
}

void Camera::Draw()
{
	//insert code HERE
	//TODO: A wireframe camera like those in Maya would be awesome
}

void Camera::Use()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos.X(),pos.Y(),pos.Z(),target.X(),target.Y(),target.Z(),up.X(),up.Y(),up.Z());
	//TODO: Auto turning around, Needs rotation member in GameObject;
}

std::pair<bool, Vec3f> Camera::getTarget() const
{
	std::pair<bool, Vec3f> ret;
	if (targetObj)
	{
		ret.first = true;
		ret.second = targetObj->getPos();
	}
	else
	{
		ret.first = false;
		ret.second = target;
	}
	return ret;
}
