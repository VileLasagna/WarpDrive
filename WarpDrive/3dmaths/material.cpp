
#include "3dmaths/material.hpp"
#include <assert.h>
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <GL/glu.h>


Material::Material() noexcept
{
    ambient = Vec3f(0.2f,0.2f,0.2f);
	specular = Vec3f(0,0,0);
    diffuse = Vec3f(0.8f,0.8f,0.8f);
	shiny = 0;
}

Vec3f Material::Ambient() const noexcept
{
	return ambient;
}

Vec3f Material::Diffuse() const noexcept
{
	return diffuse;
}

Vec3f Material::Specular() const noexcept
{
	return specular;
}

float Material::Shiny() const noexcept
{
	return shiny;
}

void Material::setAmbient(float r, float g, float b) noexcept
{
	ambient = Vec3f(r,g,b);
}

void Material::setAmbient(Vec3f v) noexcept
{
	ambient = v;
}

void Material::setDiffuse(float r, float g, float b) noexcept
{
	diffuse = Vec3f(r,g,b);
}

void Material::setDiffuse(Vec3f v) noexcept
{
	diffuse = v;
}

void Material::setSpecular(float r, float g, float b) noexcept
{
	specular = Vec3f(r,g,b);
}

void Material::setSpecular(Vec3f v) noexcept
{
	specular = v;
}

void Material::setShiny(float f) noexcept
{
	shiny = f;
}

void Material::use(Faces f) const noexcept
{
	float av[] = {ambient.X(),ambient.Y(),ambient.Z()};
	float dv[] = {diffuse.X(),diffuse.Y(),diffuse.Z()};
	float sv[] = {specular.X(),specular.Y(),specular.Z()};
	unsigned int mode;
    switch(f)
	{
    case Faces::FRONT:          mode = GL_FRONT;break;
    case Faces::BACK:           mode = GL_BACK;break;
    case Faces::FRONT_AND_BACK: mode = GL_FRONT_AND_BACK;break;
    default:                    mode = GL_FRONT;assert(0);break;
	}
	glMaterialfv(mode,GL_AMBIENT,av);
	glMaterialfv(mode,GL_DIFFUSE,dv);
	glMaterialfv(mode,GL_SPECULAR,sv);
	glMaterialf(mode,GL_SHININESS,shiny);
}

void Material::useDefault() noexcept
{

	float av[] = {0.2,0.2,0.2};
	float dv[] = {0.8,0.8,0.8};
	float sv[] = {0,0,0};
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,av);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,dv);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,sv);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,0);
}
