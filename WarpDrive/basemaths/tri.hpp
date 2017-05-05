#ifndef WD_TRI_HPP_DEFINED
#define WD_TRI_HPP_DEFINED

#include "WarpDrive/3dmaths/vertex.hpp"

class Tri
{
public:

    Tri() noexcept;
    Tri(const Vertex& a, const Vertex& b, const Vertex& c) noexcept;
    Tri(const Vertex* v) noexcept;
    Vec3<Vertex> Verts() const noexcept{return Vec3<Vertex>(A,B,C);}
    Vec3f Normal() const noexcept{return normal;}
    void draw(); //TODO: Draw functions must all accumulate to a batch that Game eventually sends out to OpenGL at the end of the Draw Loop


	

private:

	Vertex A;
	Vertex B;
	Vertex C;
    Vec3f normal;


};


#endif //WD_TRI_HPP_DEFINED
