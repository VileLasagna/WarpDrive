#ifndef WD_BOUNDING_SPHERE_HPP_DEFINED
#define WD_BOUNDING_SPHERE_HPP_DEFINED

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <memory>
#include <functional>

#include "WarpDrive/basemaths/vec3.hpp"
#include "WarpDrive/display/colour.hpp"
#include "WarpDrive/display/vertexarray.hpp"

class Sphere
{

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
    void setColour(const Colour& c) noexcept;
    void setColour(float X, float Y, float Z) noexcept;
    void setWireframe(bool b) noexcept;
    void setSlices(size_t s) noexcept {slices = s;}
    void setStacks(size_t s) noexcept {stacks = s;}
    void setModelUniform(GLint i) noexcept { modelUniform = i;}
    void setTransformUniform(GLint i) noexcept { transformUniform = i;}
    void setAmbientUniform(GLint i) noexcept { ambientUniform = i;}


    bool collides(const Sphere& other) const noexcept;

    Vec3f Centre()      const noexcept {return centre;}
    float Radius()      const noexcept {return radius;}
    Colour getColour()  const noexcept {return colour;}
    bool Wireframe()    const noexcept {return wireframe;}
    size_t Stacks()     const noexcept {return stacks;}
    size_t Slices()     const noexcept {return slices;}
    ~Sphere() = default;


private:

    void initVAO();

    Vec3f centre;
    float radius;
    Colour colour;
    bool wireframe;
    size_t slices;
    size_t stacks;
    GLint modelUniform;
    GLint transformUniform;
    GLint ambientUniform;
    std::shared_ptr<VertexArray> VAO;


};


#endif //WD_BOUNDING_SPHERE_HPP_DEFINED
