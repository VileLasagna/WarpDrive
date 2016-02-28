
#ifndef MATERIAL_H
#define MATERIAL_H

#include "BaseMaths/Vec3.hpp"


class Material
{
public:

	Material();
	Vec3f getAmbient() const;
	Vec3f getDiffuse() const;
	Vec3f getSpecular() const;
	float getShiny() const;

	void setAmbient(Vec3f v);
	void setAmbient(float r, float g, float b);
	void setDiffuse(Vec3f v);
	void setDiffuse(float r, float g, float b);
	void setSpecular(Vec3f v);
	void setSpecular(float r, float g, float b);
	void setShiny(float f);
	
	void use(int faces = 0); //0 = front, 1 = back, 2 = front+back

	static void useDefault();

private:

	Vec3f ambient;
	Vec3f diffuse;
	Vec3f specular;
	float shiny;

};

#endif //MATERIAL_H
