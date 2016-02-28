#ifndef PLANE_H
#define PLANE_H

#include "BaseMaths/Vec3.hpp"
#include "Display/Texture.hpp"
#include <utility>


class Plane
{

public:

	Plane();
	Plane (float A, float B, float C, float d);
	Plane (const Vec3f& Normal, float Distance);
	Plane (const Vec3f& P1, const Vec3f& P2, const Vec3f& P3);

	void setNormal(const Vec3f& N);
	Vec3f getNormal() const {return Vec3f(Nx,Ny,Nz);}
	Vec3f getOrigin() const {return Origin;}
	void RotateAroundOrigin(const Vec3f& angles);
	void Translate(const Vec3f& dist);
	void setDrawn(int X, int Y, float size);
	void useTexture(Texture* tex, bool Tile = false); //0 Disables (DOES NOT FREE TEXTURE IN USE!)

	void setColour(const Vec3f& rgb);
	void setColour(float r, float g, float b);
	void Draw() const;

	void DrawAsWireframe(bool b = true);
	void DrawNormal(bool b = true);




protected:

	float Nx, Ny, Nz, D, D0;
	std::pair<int,int> DrawnCells;
	float cellSize;
	Vec3f Colour;
	Vec3f Origin;
	bool drawWire;
	bool showNormal;
	Texture* TEX;
	bool tile;

};


#endif //PLANE_H
