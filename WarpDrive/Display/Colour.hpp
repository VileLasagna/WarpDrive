#ifndef COLOUR_H_DEFINED
#define COLOUR_H_DEFINED

#include "BaseMaths/Vec4.hpp"


class Colour
{
	//Class to define a Colour
	//R,G,B and A go from 0 to 1
	//Alpha 1 is 100% opaque
public:
	Colour(): r(1),g(1),b(1),a(1){}
	Colour(float red, float green, float blue, float alpha = 1): r(red),g(green),b(blue),a(alpha){}
	Colour(const Vec3f& rgb) {r = rgb.X(); g = rgb.Y(); b = rgb.Z(); a = 1;}
	Colour(const Vec4f& rgba) {r = rgba.X(); g = rgba.Y(); b = rgba.Z(); a = rgba.W();}
	float R() const {return r;}
	float G() const {return g;}
	float B() const {return b;}
	float A() const {return a;}

	void getRGB(float* dest) const {dest[0] = r; dest[1] = g; dest[2] = b;}
	Vec3f getRGB() const {return Vec3f(r,g,b);}
	void getRGBA(float* dest) const {dest[0] = r; dest[1] = g; dest[2] = b; dest[3] = a;}
	Vec4f getRGBA() const {return Vec4f(r,g,b,a);}

	void setR(float f) {r = f;}
	void setB(float f) {g = f;}
	void setG(float f) {b = f;}
	void setA(float f) {a = f;}

	bool operator== (const Colour& b) const
{
	return ( (R() == b.R()) && (G() == b.G()) && (B() == b.B()) && (A() == b.A()));
}


private:

	float r,g,b,a;

};




#endif //COLOUR_H_DEFINED
