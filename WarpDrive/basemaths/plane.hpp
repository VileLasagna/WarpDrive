#ifndef WD_PLANE_HPP_DEFINED
#define WD_PLANE_HPP_DEFINED

#include <utility>

#include "WarpDrive/basemaths/vec3.hpp"
#include "WarpDrive/display/texture.hpp"
#include "WarpDrive/display/vertexarray.hpp"

class Plane
{

public:

    Plane();
    Plane (float A, float B, float C, float D);
    Plane (const Vec3f& Normal, float Distance);
    Plane (const Vec3f& P1, const Vec3f& P2, const Vec3f& P3);

    Vec3f Normal() const noexcept{return Vec3f(nX,nY,nZ);}
    Vec3f Origin() const noexcept{return origin;}
    void rotateAroundOrigin(const Vec3f& angles);
    void translate(const Vec3f& dist)  noexcept;
    void setDrawn(int X, int Y, float size);
    void useTexture(WDTexture* tex, bool Tile = false); //0 Disables (DOES NOT FREE TEXTURE IN USE!)

    void setNormal(const Vec3f& N);
    void setColour(const Colour& c) noexcept;
    void setColour(const Vec3f& rgb) noexcept;
    void setColour(float r, float g, float b) noexcept;
    void setColour(const Vec4f& rgba) noexcept;
    void setColour(float r, float g, float b, float a) noexcept;

    void draw() const noexcept;
    void drawAsWireframe(bool b = true) noexcept;
    void drawNormal(bool b = true) noexcept;

    void setModelUniform(GLint i) noexcept { modelUniform = i;}
    void setTransformUniform(GLint i) noexcept { transformUniform = i;}




protected:

    float nX;
    float nY;
    float nZ;
    float d;
    float d0;
    std::pair<int,int> drawnCells;
    float cellSize;
    Colour colour;
    Vec3f origin;
    bool drawWire;
    bool showNormal;
    WDTexture* tex;
    bool tile;


    GLint modelUniform;
    GLint transformUniform;
    VertexArray  VAO;
};

#endif //WD_PLANE_HPP_DEFINED
