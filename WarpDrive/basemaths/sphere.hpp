#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include<memory>
#include <GL/glu.h>


#include "basemaths/vec3.hpp"
#include "display/rgbcolour.hpp"

//Forward Declarations
class GLUquadric;
auto gluQuadDeleter = [](GLUquadric* p){gluDeleteQuadric(p);};
using ptr_GLUquad = std::unique_ptr<GLUquadric,decltype(gluQuadDeleter)>;

class Sphere
{
    static constexpr const unsigned int roundness = 24;

public:

	Sphere();
	Sphere(const Vec3f& centre, float r);
	Sphere(float centreX, float centreY, float centreZ, float R);

	void Draw() const;
	void setPos(const Vec3f& pos);
	void setPos(float X, float Y, float Z);
	void setRadius(float R);
	void setColour(const Vec3f& pos);
	void setColour(float X, float Y, float Z);
    void setWireframe(bool b);

	bool collides(const Sphere& other) const;

    Vec3f getCentre()   const   {return Centre;}
    float getRadius()   const   {return Radius;}
    bool getWireframe() const   {return wireframe;}
	~Sphere() = default;


private:


	Vec3f Centre;
	float Radius;
	ptr_GLUquad quadric;
	GLRGBColour colour;
    bool wireframe;

	ptr_GLUquad initQuadric();

};


#endif //BOUNDING_SPHERE_H
