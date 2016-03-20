#ifndef WD_PLANE_HPP_DEFINED
#define WD_PLANE_HPP_DEFINED

#include <utility>

#include "basemaths/vec3.hpp"
#include "display/texture.hpp"

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
	void useTexture(Texture* tex, bool Tile = false); //0 Disables (DOES NOT FREE TEXTURE IN USE!)

    void setNormal(const Vec3f& N);
    void setColour(const Vec3f& rgb) noexcept;
    void setColour(float r, float g, float b) noexcept;

    void draw() const noexcept;
    void drawAsWireframe(bool b = true) noexcept;
    void drawNormal(bool b = true) noexcept;




protected:

    float nX;
    float nY;
    float nZ;
    float d;
    float d0;
    std::pair<int,int> drawnCells;
	float cellSize;
    Vec3f colour;
    Vec3f origin;
	bool drawWire;
	bool showNormal;
    Texture* tex;
	bool tile;

};


#endif //WD_PLANE_HPP_DEFINED
