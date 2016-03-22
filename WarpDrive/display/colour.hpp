#ifndef WD_COLOUR_HPP_DEFINED
#define WD_COLOUR_HPP_DEFINED

#include "basemaths/vec4.hpp"
#include "basesystem/util.hpp"

class Colour
{
	//Class to define a Colour
	//R,G,B and A go from 0 to 1
	//Alpha 1 is 100% opaque
public:

    Colour() noexcept: r(1),g(1),b(1),a(1){}
    Colour(float red, float green, float blue, float alpha = 1) noexcept: r(red),g(green),b(blue),a(alpha){}
    Colour(const Vec3f& rgb) noexcept {r = rgb.X(); g = rgb.Y(); b = rgb.Z(); a = 1;}
    Colour(const Vec4f& rgba) noexcept {r = rgba.X(); g = rgba.Y(); b = rgba.Z(); a = rgba.W();}
    float R() const noexcept {return r;}
    float G() const noexcept {return g;}
    float B() const noexcept {return b;}
    float A() const noexcept {return a;}

    void RGB(float* dest) const {dest[0] = r; dest[1] = g; dest[2] = b;}
    Vec3f RGB() const {return Vec3f(r,g,b);}
    void RGBA(float* dest) const {dest[0] = r; dest[1] = g; dest[2] = b; dest[3] = a;}
    Vec4f RGBA() const {return Vec4f(r,g,b,a);}

	void setR(float f) {r = f;}
	void setB(float f) {g = f;}
	void setG(float f) {b = f;}
	void setA(float f) {a = f;}

    bool operator== (const Colour& other) const
    {
        return ( WrpDrv::flEquals(R(),other.R()) && WrpDrv::flEquals(G(),other.G()) && WrpDrv::flEquals(B(), other.B()) && WrpDrv::flEquals(A(), other.A()));
    }

private:

	float r,g,b,a;

};

#endif //WD_COLOUR_HPP_DEFINED
