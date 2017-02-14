#include "display/camera.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <math.h>
#include <GL/glu.h>

#include "basesystem/util.hpp"

#include "basemaths/sphere.hpp"

Camera::Camera():
	up(Vec3f(0,1,0)),
	targetObj(0),
    relativePos(),
	orbitFactors(1,0,1),
	orbitRadius(0),
	orbitPeriod(1),
	time(0)
{
     type = "Camera";
     removeMe = false;
}

void Camera::update()
{

    GameObject::update();
    if(targetObj != nullptr)
	{
        target = targetObj->Position();
        if(WrpDrv::flEquals(orbitRadius,0))
        {
            pos = target + relativePos;
        }

	}
	else
	{
    /*	vel += accel*DisplayManager::instance()->getDtSecs();
        pos += vel*DisplayManager::instance()->getDtSecs();*/
	}
    if(!WrpDrv::flEquals(orbitRadius, 0))
    {
        time += DisplayManager::instance()->Dt();
        //relativePos = Vec3f(orbitFactors.X()*orbitRadius*sin(time*(orbitPeriod*0.5f)),orbitFactors.Y()*orbitRadius*sin(time*(orbitPeriod*0.5f)),orbitFactors.Z()*orbitRadius*sin(time*(orbitPeriod*0.5f)));
        Vec3f direction = Vec3f(static_cast<float>( orbitFactors.X()*sin(time*(orbitPeriod*0.5f)*0.001f) ),
                                static_cast<float>( orbitFactors.Y()*sin(time*(orbitPeriod*0.5f)*0.001f) ),
                                static_cast<float>( orbitFactors.Z()*cos(time*(orbitPeriod*0.5f)*0.001f) ) );
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
    worldX = 0;
    worldY = 0;
    worldZ = 0;

    auto proj  = DisplayManager::instance()->ProjectionMatrix();
    auto model = DisplayManager::instance()->ModelviewMatrix();
    auto view  = DisplayManager::instance()->Viewport();

    gluUnProject(x,view[3] - y, 0 , model, proj, view, &worldX, &worldY, &worldZ);

    return Ray( LineSeg(pos, Vec3f(static_cast<float>(worldX),static_cast<float>(worldY),static_cast<float>(worldZ) ) ) );

}

void Camera::draw() const
{
	//insert code HERE
	//TODO: A wireframe camera like those in Maya would be awesome
}

void Camera::use() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(pos.X(),pos.Y(),pos.Z(),target.X(),target.Y(),target.Z(),up.X(),up.Y(),up.Z());
    //DisplayManager::instance()->updateMatrices();
	//TODO: Auto turning around, Needs rotation member in GameObject;
}

std::pair<bool, Vec3f> Camera::Target() const
{
	std::pair<bool, Vec3f> ret;
	if (targetObj)
	{
		ret.first = true;
        ret.second = targetObj->Position();
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

