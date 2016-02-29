#include "display/camera.hpp"
#include "basemaths/sphere.hpp"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <GL/glu.h>
#include<math.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreorder"

Camera::Camera():
	up(Vec3f(0,1,0)),
	targetObj(0),
	orbitFactors(1,0,1),
	relativePos(),
	orbitRadius(0),
	orbitPeriod(1),
	time(0)
{
     type = "Camera";
     removeMe = false;
}

void Camera::Update()
{

	GameObject::Update();
	if(targetObj)
	{
        target = targetObj->getPos();
        if(orbitRadius == 0)
        {
            pos = target + relativePos;
        }

	}
	else
	{
    /*	vel += accel*DisplayManager::instance()->getDtSecs();
        pos += vel*DisplayManager::instance()->getDtSecs();*/
	}
    if(orbitRadius != 0)
    {
        time += DisplayManager::instance()->getDtSecs();
        //relativePos = Vec3f(orbitFactors.X()*orbitRadius*sin(time*(orbitPeriod*0.5f)),orbitFactors.Y()*orbitRadius*sin(time*(orbitPeriod*0.5f)),orbitFactors.Z()*orbitRadius*sin(time*(orbitPeriod*0.5f)));
        Vec3f direction = Vec3f(orbitFactors.X()*sin(time*(orbitPeriod*0.5f)),   orbitFactors.Y()*sin(time*(orbitPeriod*0.5f)),   orbitFactors.Z()*cos(time*(orbitPeriod*0.5f)));
        direction.normalise();
        relativePos = direction * orbitRadius;
        pos = target+relativePos;
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

Ray Camera::traceRay(int x, int y) const noexcept
{
    GLdouble worldX, worldY, worldZ;
    //GLfloat winZ;
    worldX = 0;
    worldY = 0;
    worldZ = 0;
    //winZ = 0;
    GLdouble model[16];
    GLdouble proj[16];
    GLint viewport[4];

    glGetDoublev(GL_MODELVIEW_MATRIX,model);

    glGetDoublev(GL_PROJECTION_MATRIX,proj);
    glGetIntegerv(GL_VIEWPORT,viewport);


//    glReadPixels(e.x, viewport[3] - e.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);


   auto res = gluUnProject(x,viewport[3] - y, 0 , model, proj, viewport, &worldX, &worldY, &worldZ);

   return Ray( LineSeg(pos, Vec3f(worldX,worldY,worldZ) ) );

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

void Camera::orbit(float X, float Y, float Z, float radius, float periodSecs)
{
    orbitFactors = Vec3f(X,Y,Z);
    orbitRadius = radius;
    orbitPeriod = periodSecs;
}

#pragma clang diagnostic pop

