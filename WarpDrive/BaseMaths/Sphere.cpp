#include "BaseMaths/Sphere.hpp"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <math.h>
#include <assert.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wreorder"

Sphere::Sphere():
	Centre(Vec3f(0,0,0)),
	Radius(0),
	colour(GLRGBColour(1,1,1)),
    quadric(initQuadric()),
    wireframe(true)
    {}


Sphere::Sphere(const Vec3f& centre, float r):
	Centre(centre),
	Radius(r),
	colour(GLRGBColour(1,1,1)),
    quadric(initQuadric()),
    wireframe(true)
    {}

Sphere::Sphere(float centreX, float centreY, float centreZ, float R):
	Centre{Vec3f{centreX,centreY,centreZ}},
	Radius{R},
	colour{GLRGBColour{1,1,1}},
    quadric(initQuadric()),
    wireframe(true)
    {}


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
    colour = GLRGBColour{R,G,B};
}

void Sphere::setWireframe(bool b)
{
    wireframe = b;
    if (b)
    {
        gluQuadricDrawStyle(quadric.get(), GLU_LINE);
    }
    else
    {
        gluQuadricDrawStyle(quadric.get(), GLU_FILL);

    }
}

void Sphere::setColour(const Vec3f& pos)
{
    colour = GLRGBColour(pos.R(),pos.G(),pos.B());
}

void Sphere::setRadius(float R)
{
	Radius = R;
}

bool Sphere::collides(const Sphere& other) const
{
	return ( (Radius+other.Radius)*(Radius+other.Radius) >= 
			    ( (Centre.X()-other.Centre.X())*(Centre.X()-other.Centre.X()) +
				 (Centre.Y()-other.Centre.Y())*(Centre.Y()-other.Centre.Y()) +
				 (Centre.Z()-other.Centre.Z())*(Centre.Z()-other.Centre.Z())  )
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
        gluSphere(quadric.get(), Radius,roundness,roundness);

    glPopMatrix();

    glColor3f(1,1,1);
    glDisable(GL_COLOR_MATERIAL);

}


ptr_GLUquad Sphere::initQuadric()
{
    auto quad = ptr_GLUquad(gluNewQuadric(), gluQuadDeleter);
    assert(quad);
    gluQuadricDrawStyle(quad.get(), GLU_LINE);
    gluQuadricOrientation(quad.get(), GLU_OUTSIDE);
    return quad;

}

#pragma clang diagnostic pop
