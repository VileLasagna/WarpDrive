#include "BaseMaths/Sphere.h"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <GL/GLU.h>
#include <math.h>
#include <assert.h>


Sphere::Sphere():Centre(Vec3f(0,0,0)), Radius(0), quadric(0), colour(Vec3f(1,1,1))
{
    //nullSphere
    initQuadric();
}

Sphere::Sphere(const Vec3f& centre, float r): Centre(centre), Radius(r), quadric(0), colour(Vec3f(1,1,1))
{
    initQuadric();
}

Sphere::Sphere(float centreX, float centreY, float centreZ, float R): Centre(Vec3f(centreX,centreY,centreZ)), Radius(R), quadric(0), colour(Vec3f(1,1,1))
{
    initQuadric();
}

void Sphere::setPos(float X, float Y, float Z)
{
	Centre = Vec3f(X,Y,Z);
}

void Sphere::setPos(const Vec3f& pos)
{
	Centre = pos;
}

void Sphere::setColour(float R, float G, float B)
{
    colour = Vec3f(R,G,B);
}

void Sphere::setColour(const Vec3f& pos)
{
    colour = pos;
}

void Sphere::setRadius(float R)
{
	Radius = R;
}

bool Sphere::collides(const Sphere& other) const
{
	return ( (Radius+other.Radius)*(Radius+other.Radius) >= 
				(
				(Centre.X()-other.Centre.X())*(Centre.X()-other.Centre.X()) + 
				(Centre.Y()-other.Centre.Y())*(Centre.Y()-other.Centre.Y()) + 
				(Centre.Z()-other.Centre.Z())*(Centre.Z()-other.Centre.Z())) 
				);
}

void Sphere::Draw() const
{


    //TODO: LIGHTING
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(colour.R(),colour.G(), colour.B());
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glPushMatrix();
        glTranslatef(Centre.X(),Centre.Y(),Centre.Z());
        gluSphere(quadric, Radius,16,16);
    glPopMatrix();

    glColor3f(1,1,1);
    glDisable(GL_COLOR_MATERIAL);

}

Sphere::~Sphere()
{
    gluDeleteQuadric(quadric);
}
void Sphere::initQuadric()
{
    quadric = gluNewQuadric();
    assert(quadric);
    gluQuadricDrawStyle(quadric, GLU_LINE);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);

}
