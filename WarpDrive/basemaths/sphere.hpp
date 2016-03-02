#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include<memory>
#include <GL/glu.h>


#include "basemaths/vec3.hpp"
#include "display/rgbcolour.hpp"

//Forward Declarations
class GLUquadric;
auto gluQuadDeleter = [](GLUquadric* p){gluDeleteQuadric(p);};
using ptr_GLUquad = std::unique_ptr<GLUquadric,decltype(gluQuadDeleter)>;

class Sphere
{
    static constexpr const unsigned int roundness = 24;

public:

    Sphere() noexcept;
    Sphere(const Vec3f& centre, float r) noexcept;
    Sphere(float centreX, float centreY, float centreZ, float R) noexcept;

    Sphere(const Sphere& other) noexcept;
    Sphere(Sphere&& other) noexcept;

    Sphere& operator=(const Sphere& other) noexcept;
    Sphere& operator=(Sphere&& other) noexcept;

    void Draw() const noexcept;
    void setPos(const Vec3f& pos) noexcept;
    void setPos(float X, float Y, float Z) noexcept;
    void setRadius(float R) noexcept;
    void setColour(const Vec3f& c) noexcept;
    void setColour(const GLRGBColour& c) noexcept;
    void setColour(float X, float Y, float Z) noexcept;
    void setWireframe(bool b) noexcept;

    bool collides(const Sphere& other) const noexcept;

    Vec3f Centre()       const noexcept {return centre;}
    float Radius()       const noexcept {return radius;}
    GLRGBColour Colour() const noexcept {return colour;}
    bool Wireframe()     const noexcept {return wireframe;}
	~Sphere() = default;


private:


    Vec3f centre;
    float radius;
	GLRGBColour colour;
    bool wireframe;

    ptr_GLUquad quadric;


    ptr_GLUquad initQuadric() noexcept;

};


#endif //BOUNDING_SPHERE_H
