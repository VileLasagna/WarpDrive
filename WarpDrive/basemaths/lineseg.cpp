#include "WarpDrive/basemaths/lineseg.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32
#include <GL/glu.h>

void LineSeg::draw() noexcept
{
    glBegin(GL_LINES);
        glVertex3f(p0.X(), p0.Y(), p0.Z());
        glVertex3f(p1.X(), p1.Y(), p1.Z());
    glEnd();
}

bool LineSeg::parallel(const LineSeg& other) const
{
    Vec3f thisNorm = p1-p0;
    Vec3f otherNorm = other.End() - other.Start();
    thisNorm.normalise();
    otherNorm.normalise();
    return (thisNorm == otherNorm);
}

std::pair<bool, Vec3f> LineSeg::intersects(const LineSeg& ) const
{

    //TODO: Definition
    std::pair<bool,Vec3f> ret;
    ret.first = false;

    return ret;
}

float LineSeg::sqDistToPoint ( const Vec3f& p) const
{
    Vec3f M = p1-p0;
    if (WrpDrv::flEquals(M.sqMod(), 0)) //p1 == p0
    {
        return (p-p1).sqMod();
    }
    float t = dotProd(M,p-p0)/dotProd(M,M);
    Vec3f ret;
    if (t<=0) { ret = p-p0;}
    if(t>=1) { ret = p-p1;}
    if (t>0 && t<1) {ret = p0*(1-t) + p1*t;}
    return ret.sqMod();
}
