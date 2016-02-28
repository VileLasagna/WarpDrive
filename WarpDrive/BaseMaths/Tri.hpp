#ifndef TRI_H_DEFINED
#define TRI_H_DEFINED

#include "3DMaths/Vertex.hpp"

class Tri
{
public:

	Tri();
	Tri(const Vertex& a, const Vertex& b, const Vertex& c);
	Tri(const Vertex* v);
	Vec3<Vertex> getVerts() const {return Vec3<Vertex>(A,B,C);}
	Vec3f getNormal() const {return Normal;}
	void Draw(); //TODO: Draw functions must all accumulate to a batch that Game eventually sends out to OpenGL at the end of the Draw Loop


	

private:

	Vertex A;
	Vertex B;
	Vertex C;
	Vec3f Normal;


};


#endif //TRI_H_DEFINED
