#include "WarpDrive/3dmaths/vertex.hpp"

#include "WarpDrive/basesystem/util.hpp"

Vertex::Vertex(const Vec3f& p) noexcept
{
    pos = p;
    Vertex::LastNormal( &normal );
    Vertex::LastAmbient( &ambient );
    Vertex::LastDiffuse( &diffuse );
    Vertex::LastShiny( &shiny );
}

Vertex::Vertex(const Vec3f& p, const Vec3f& norm, const Vec2f& uvcoords , const Colour& diff, const Colour& amb, const Colour& spec, float shinyness) noexcept
{
    pos = p;
    normal = norm;
    Vertex::LastNormal(&normal, true);
    uv = uvcoords;
    Colour def(-1.0f,-1.0f,-1.0f,-1.0f);
    if (diffuse == def)
    {
        Vertex::LastDiffuse(&diffuse);
    }
    else
    {
        diffuse = diff;
        Vertex::LastDiffuse(&diffuse, true);
    }
    if (ambient == def)
    {
        Vertex::LastAmbient(&ambient);
    }
    else
    {
        ambient = amb;
        Vertex::LastAmbient(&ambient, true);
    }

    if (specular == def )
    {
        Vertex::LastSpecular(&specular);
    }
    else
    {
        specular = spec;
        Vertex::LastSpecular(&specular, true);
    }
    if (WrpDrv::flEquals(shinyness, -1))
    {
        Vertex::LastShiny(&shiny);
    }
    else
    {
        shiny = shinyness;
        Vertex::LastShiny(&shiny, true);
    }


}

void Vertex::LastAmbient(Colour *v, bool set) noexcept
{
    static Colour Ambient(0.1f,0.1f,0.1f);
    if (set)
    {
        Ambient = *v;
    }
    else
    {
        *v = Ambient;
    }
}

void Vertex::LastDiffuse(Colour *v, bool set) noexcept
{
    static Colour diffuse(1,1,1);
    if (set)
    {
        diffuse = *v;
    }
    else
    {
        *v = diffuse;
    }
}

void Vertex::LastNormal(Vec3f *v, bool set) noexcept
{
    static Vec3f normal(0,0,1);
    if (set)
    {
        normal = *v;
    }
    else
    {
        *v = normal;
    }
}
 
void Vertex::LastShiny(float *f, bool set) noexcept
{
    static float shiny = 100;
    if (set)
    {
        shiny = *f;
    }
    else
    {
        *f = shiny;
    }
}

void Vertex::LastSpecular(Colour* v, bool set) noexcept
{
    static Colour specular(1,1,1);
    if(set)
    {
        specular = *v;
    }
    else
    {
        *v = specular;
    }
}

