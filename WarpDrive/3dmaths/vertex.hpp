
#ifndef VERTEX_H
#define VERTEX_H


#include "display/colour.hpp"


class Vertex
{
public:

	Vertex(const Vec3f& pos = Vec3f(0,0,0));
	Vertex(const Vec3f& pos, const Vec3f& normal, const Vec2f& uv = Vec2f(0,0), const Colour& diffuse = Colour(-1,-1,-1,-1), const Colour& ambient = Colour(-1.0f,-1.0f,-1.0f,-1.0f), const Colour& specular = Colour(-1.0f,-1.0f,-1.0f,-1.0f), float shinyness = -1);

	Vec3f getPos() const {return Pos;}
	Vec3f getNormal() const {return Normal;}
	Vec2f getUV() const {return UV;}
	Colour getAmbient() const {return Ambient;}
	Colour getDiffuse() const {return Diffuse;}
	Colour getSpecular() const {return Specular;}
	float getShiny() const {return Shiny;} //1 to 128.0

private:

	static void LastNormal(Vec3f* v, bool set = false);
	static void LastAmbient(Colour* v, bool set = false);
	static void LastDiffuse(Colour* v, bool set = false);
	static void LastSpecular(Colour* v, bool set = false);
	static void LastShiny(float* f, bool set = false);
	
	Vec3f Pos;
	Vec3f Normal;
	Vec2f UV;
	Colour Ambient;
	Colour Diffuse;
	Colour Specular;
	float Shiny;


};


#endif //VERTEX_H
