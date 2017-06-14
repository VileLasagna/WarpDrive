#ifndef WD_BOUNDING_SPHERE_HPP_DEFINED
#define WD_BOUNDING_SPHERE_HPP_DEFINED

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <memory>
#include <functional>
#include <GL/glu.h>


#include "WarpDrive/basemaths/vec3.hpp"
#include "WarpDrive/display/rgbcolour.hpp"

//Forward Declarations
class GLUquadric;
static std::function<void(GLUquadric*)> gluQuadDeleter = [](GLUquadric* p){gluDeleteQuadric(p);};
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

    void draw() const noexcept;
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


#endif //WD_BOUNDING_SPHERE_HPP_DEFINED
