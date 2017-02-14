#include "basemaths/sphere.hpp"
#ifdef WIN32
    #include <Windows.h>
#endif //WIN32
#include <math.h>
#include <assert.h>


Sphere::Sphere() noexcept:
    centre(Vec3f(0,0,0)),
    radius(0),
	colour(GLRGBColour(1,1,1)),
    wireframe(true),
    quadric(initQuadric())
    {}


Sphere::Sphere(const Vec3f& pos, float r) noexcept:
    centre(pos),
    radius(r),
	colour(GLRGBColour(1,1,1)),
    wireframe(true),
    quadric(initQuadric())
    {}

Sphere::Sphere(float centreX, float centreY, float centreZ, float R) noexcept:
    centre{Vec3f{centreX,centreY,centreZ}},
    radius{R},
	colour{GLRGBColour{1,1,1}},
    wireframe(true),
    quadric(initQuadric())
{}

Sphere::Sphere(const Sphere& other) noexcept
   :centre{other.Centre()},
    radius{other.Radius()},
    colour{other.Colour()},
    wireframe{other.Wireframe()},
    quadric(initQuadric())
{}

Sphere::Sphere(Sphere&& other) noexcept
    :centre{other.Centre()},
     radius{other.Radius()},
     colour{other.Colour()},
     wireframe{other.Wireframe()},
     quadric(std::move(other.quadric))
{}

Sphere& Sphere::operator=(const Sphere& other) noexcept
{
    colour = other.Colour();
    radius = other.Radius();
    centre = other.Centre();
    wireframe = other.Wireframe();
    if(quadric.get() == nullptr)
    {
        initQuadric();
    }
    return *this;
}

Sphere& Sphere::operator=(Sphere&& other) noexcept
{
    colour = other.Colour();
    radius = other.Radius();
    centre = other.Centre();
    wireframe = other.Wireframe();
    quadric = std::move(other.quadric);

    return *this;
}


void Sphere::setPos(float X, float Y, float Z) noexcept
{
    centre = Vec3f(X,Y,Z);
}

void Sphere::setPos(const Vec3f& pos) noexcept
{
    centre = pos;
}

void Sphere::setColour(float R, float G, float B) noexcept
{
    colour = GLRGBColour{R,G,B};
}

void Sphere::setWireframe(bool b) noexcept
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

void Sphere::setColour(const Vec3f& c) noexcept
{
    colour = GLRGBColour(c.R(),c.G(),c.B());
}

void Sphere::setColour(const GLRGBColour& c) noexcept
{
    colour = c;
}

void Sphere::setRadius(float R) noexcept
{
    radius = R;
}

bool Sphere::collides(const Sphere& other) const noexcept
{
    return (    (radius+other.Radius())*(radius+other.Radius()) >=
                ( (centre.X()-other.Centre().X())*(centre.X()-other.Centre().X()) +
                  (centre.Y()-other.Centre().Y())*(centre.Y()-other.Centre().Y()) +
                  (centre.Z()-other.Centre().Z())*(centre.Z()-other.Centre().Z()) )  );
}

void Sphere::draw() const noexcept
{


    //TODO: LIGHTING
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(colour.R(),colour.G(), colour.B());
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

    glPushMatrix();

        glTranslatef(centre.X(),centre.Y(),centre.Z());
        gluSphere(quadric.get(), radius,roundness,roundness);

    glPopMatrix();

    glColor3f(1,1,1);
    glDisable(GL_COLOR_MATERIAL);

}


ptr_GLUquad Sphere::initQuadric() noexcept
{
    auto quad = ptr_GLUquad(gluNewQuadric(), gluQuadDeleter);
    assert(quad);
    gluQuadricDrawStyle(quad.get(), GLU_LINE);
    gluQuadricOrientation(quad.get(), GLU_OUTSIDE);
    return quad;

}

