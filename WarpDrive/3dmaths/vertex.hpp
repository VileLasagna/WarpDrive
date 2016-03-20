#ifndef WD_VERTEX_HPP_DEFINED
#define WD_VERTEX_HPP_DEFINED


#include "display/colour.hpp"


class Vertex
{
public:

    Vertex(const Vec3f& pos = Vec3f(0,0,0))noexcept;
    Vertex(const Vec3f& pos, const Vec3f& normal,
           const Vec2f& uv = Vec2f(0,0),
           const Colour& diffuse = Colour(-1,-1,-1,-1),
           const Colour& ambient = Colour(-1.0f,-1.0f,-1.0f,-1.0f),
           const Colour& specular = Colour(-1.0f,-1.0f,-1.0f,-1.0f),
           float shinyness = -1) noexcept;

    Vec3f Position()    const noexcept {return pos;}
    Vec3f Normal()      const noexcept {return normal;}
    Vec2f UV()          const noexcept {return uv;}
    Colour Ambient()    const noexcept {return ambient;}
    Colour Diffuse()    const noexcept {return diffuse;}
    Colour Specular()   const noexcept {return specular;}
    float Shiny()       const noexcept {return shiny;} //1 to 128.0

private:

    static void LastNormal(Vec3f* v, bool set = false)  noexcept;
    static void LastAmbient(Colour* v, bool set = false)  noexcept;
    static void LastDiffuse(Colour* v, bool set = false)  noexcept;
    static void LastSpecular(Colour* v, bool set = false)  noexcept;
    static void LastShiny(float* f, bool set = false)  noexcept;
	
    Vec3f pos;
    Vec3f normal;
    Vec2f uv;
    Colour ambient;
    Colour diffuse;
    Colour specular;
    float shiny;


};


#endif //WD_VERTEX_HPP_DEFINED
