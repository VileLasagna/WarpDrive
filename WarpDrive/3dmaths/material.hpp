
#ifndef WD_MATERIAL_HPP_DEFINED
#define WD_MATERIAL_HPP_DEFINED

#include "basemaths/vec3.hpp"


class Material
{
public:

    enum class Faces{FRONT = 0, BACK = 1, FRONT_AND_BACK = 2};

    Material() noexcept;
    Vec3f Ambient() const noexcept;
    Vec3f Diffuse() const noexcept;
    Vec3f Specular() const noexcept;
    float Shiny() const noexcept;

    void setAmbient(Vec3f v) noexcept;
    void setAmbient(float r, float g, float b) noexcept;
    void setDiffuse(Vec3f v) noexcept;
    void setDiffuse(float r, float g, float b) noexcept;
    void setSpecular(Vec3f v) noexcept;
    void setSpecular(float r, float g, float b) noexcept;
    void setShiny(float f) noexcept;
	
    void use(Faces f = Faces::FRONT) const noexcept; //0 = front, 1 = back, 2 = front+back

    static void useDefault() noexcept;

private:

	Vec3f ambient;
	Vec3f diffuse;
	Vec3f specular;
	float shiny;

};

#endif //WD_MATERIAL_HPP_DEFINED
