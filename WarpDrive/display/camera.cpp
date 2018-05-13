#include "WarpDrive/display/camera.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <math.h>
#include <GL/glew.h>

#include "WarpDrive/basesystem/util.hpp"

#include "WarpDrive/basemaths/sphere.hpp"

Camera::Camera():
    up(Vec3f(0,1,0)),
    targetObj(0),
    relativePos(0,0,0),
    orbitAxis(0,1,0),
    orbitZero(0,0,0),
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
    }
    else
    {
        /*vel += accel*DisplayManager::instance()->getDtSecs();
        pos += vel*DisplayManager::instance()->getDtSecs();*/
    }
    if(orbitZero.sqMod() > WrpDrv::flEpsilon)
    {
        /// Taken from https://sites.google.com/site/glennmurray/Home/rotation-matrices-and-formulas
        time += DisplayManager::instance()->Dt();
        float angle = WrpDrv::Pi*time/(orbitPeriod*500.f);

        float a = target.X();
        float b = target.Y();
        float c = target.Z();

        float u = orbitAxis.X();
        float v = orbitAxis.Y();
        float w = orbitAxis.Z();

        float x = orbitZero.X();
        float y = orbitZero.Y();
        float z = orbitZero.Z();

        float s = std::sin(angle);
        float cs = std::cos(angle);

        relativePos.setX(   (  a*((v*v)+(w*w)) - ( u*((b*v)+(c*w)-(u*x)-(v*y)-(w*z)) )  )*(1-cs)
                    + (x*cs)
                    + ( s*( (b*w)-(c*v)-(w*y)+(v*z) ))     );

        relativePos.setY(   (  b*((u*u)+(w*w)) - ( v*((a*u)+(c*w)-(u*x)-(v*y)-(w*z)) )  )*(1-cs)
                    + (y*cs)
                    + ( s*( (c*u)-(a*w)+(w*x)-(u*z) ))     );

        relativePos.setZ(   (  c*((u*u)+(v*v)) - ( w*((a*u)+(b*v)-(u*x)-(v*y)-(w*z)) )  )*(1-cs)
                    + (z*cs)
                    + ( s*( (a*v)-(b*u)-(v*x)+(u*y) ) )    );

        pos = relativePos + target;

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
    orbitZero = Relative;
}

void Camera::setPerspective(float fovY, float ratio, float zNear, float zFar)
{
    projection.setPerspective(fovY, ratio, zNear, zFar);
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

Matrix44 Camera::View() const
{
    Matrix44 view;
    view.lookAt(pos, target, up);
    return view;
    //gluLookAt(pos.X(),pos.Y(),pos.Z(),target.X(),target.Y(),target.Z(),up.X(),up.Y(),up.Z());
}

const Matrix44& Camera::Projection() const
{
    return projection;
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

void Camera::orbit(float X, float Y, float Z, float periodSecs, Vec3f relativeStart)
{
    orbitAxis = Vec3f(X,Y,Z);
    orbitAxis.normalise();
    orbitPeriod = periodSecs;
    if(relativeStart.sqMod() > WrpDrv::flEpsilon)
    {
        orbitZero = target + relativeStart;
    }
    else
    {
        if(relativePos.sqMod() <= WrpDrv::flEpsilon)
        {
            relativePos = pos - target;
        }
        orbitZero = target + relativePos;
    }
}

void Camera::orbit(Vec3f axis, float periodSecs, Vec3f relativeStart)
{
    orbitAxis = axis;
    orbitAxis.normalise();
    orbitPeriod = periodSecs;
    if(relativeStart.sqMod() > WrpDrv::flEpsilon)
    {
        orbitZero = target + relativeStart;
    }
    else
    {
        if(relativePos.sqMod() <= WrpDrv::flEpsilon)
        {
            relativePos = pos - target;
        }
        orbitZero = target + relativePos;
    }
}
