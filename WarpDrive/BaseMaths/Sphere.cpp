#include "BaseMaths/Sphere.h"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <GL/glut.h>
#include <math.h>


Sphere::Sphere()
{
	//nullSphere
	Centre = Vec3f(0,0,0);
	Radius = 0;
}

Sphere::Sphere(const Vec3f& centre, float r)
{
	Centre = centre;
	Radius = r;
}

Sphere::Sphere(float centreX, float centreY, float centreZ, float R)
{
	Centre = Vec3f(centreX,centreY,centreZ);
	Radius = R;
}

void Sphere::setPos(float X, float Y, float Z)
{
	Centre = Vec3f(X,Y,Z);
}

void Sphere::setPos(const Vec3f& pos)
{
	Centre = pos;
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
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_COLOR);
	glColor3f(1,0,1);
	//glTranslatef(Centre.X(),Centre.Y(),Centre.Z());
	glutWireSphere(Radius,8,8);
	glColor3f(1,1,1);
	glDisable(GL_COLOR);
	glEnable(GL_LIGHTING);
	glPopMatrix();
}
