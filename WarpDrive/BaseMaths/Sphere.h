#ifndef BOUNDING_SPHERE_H
#define BOUNDING_SPHERE_H

#include "BaseMaths/Vec3.h"

//Forward Declarations
class GLUquadric;


class Sphere
{
public:

	Sphere();
	Sphere(const Vec3f& centre, float r);
	Sphere(float centreX, float centreY, float centreZ, float R);

	void Draw() const;
	void setPos(const Vec3f& pos);
	void setPos(float X, float Y, float Z);
	void setRadius(float R);

	bool collides(const Sphere& other) const;

	Vec3f getCentre() const {return Centre;}
	float getRadius() const {return Radius;}
    ~Sphere();


private:

	Vec3f Centre;
	float Radius;
    GLUquadric* quadric;

    void initQuadric();

};


#endif //BOUNDING_SPHERE_H
