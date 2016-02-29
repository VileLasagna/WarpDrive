
#include "3dmaths/material.hpp"
#include <assert.h>
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <GL/glu.h>


Material::Material()
{
    ambient = Vec3f(0.2f,0.2f,0.2f);
	specular = Vec3f(0,0,0);
    diffuse = Vec3f(0.8f,0.8f,0.8f);
	shiny = 0;
}

Vec3f Material::getAmbient() const
{
	return ambient;
}

Vec3f Material::getDiffuse() const
{
	return diffuse;
}

Vec3f Material::getSpecular() const
{
	return specular;
}

float Material::getShiny() const
{
	return shiny;
}

void Material::setAmbient(float r, float g, float b)
{
	ambient = Vec3f(r,g,b);
}

void Material::setAmbient(Vec3f v)
{
	ambient = v;
}

void Material::setDiffuse(float r, float g, float b)
{
	diffuse = Vec3f(r,g,b);
}

void Material::setDiffuse(Vec3f v)
{
	diffuse = v;
}

void Material::setSpecular(float r, float g, float b)
{
	specular = Vec3f(r,g,b);
}

void Material::setSpecular(Vec3f v)
{
	specular = v;
}

void Material::setShiny(float f)
{
	shiny = f;
}

void Material::use(int faces)
{
	float av[] = {ambient.X(),ambient.Y(),ambient.Z()};
	float dv[] = {diffuse.X(),diffuse.Y(),diffuse.Z()};
	float sv[] = {specular.X(),specular.Y(),specular.Z()};
	unsigned int mode;
	switch(faces)
	{
	case 0: mode = GL_FRONT;break;
	case 1: mode = GL_BACK;break;
	case 2: mode = GL_FRONT_AND_BACK;break;
	default: mode = GL_FRONT;assert(0);break;
	}
	glMaterialfv(mode,GL_AMBIENT,av);
	glMaterialfv(mode,GL_DIFFUSE,dv);
	glMaterialfv(mode,GL_SPECULAR,sv);
	glMaterialf(mode,GL_SHININESS,shiny);
}

void Material::useDefault()
{

	float av[] = {0.2,0.2,0.2};
	float dv[] = {0.8,0.8,0.8};
	float sv[] = {0,0,0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,av);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dv);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,sv);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
}
