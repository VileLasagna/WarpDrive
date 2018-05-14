#include "WarpDrive/basemaths/sphere.hpp"
#ifdef WIN32
    #include <Windows.h>
#endif //WIN32
#include <math.h>
#include <assert.h>

#include "WarpDrive/basemaths/matrix44.hpp"


Sphere::Sphere() noexcept:
    centre(Vec3f(0,0,0)),
    radius(0),
    colour(Colour(1,1,1)),
    wireframe(true),
    stacks(24),
    slices(24)
{
    initVAO();
}


Sphere::Sphere(const Vec3f& pos, float r) noexcept:
    centre(pos),
    radius(r),
    colour(Colour(1,1,1)),
    wireframe(true),
    stacks(24),
    slices(24)
{
    initVAO();
}

Sphere::Sphere(float centreX, float centreY, float centreZ, float R) noexcept:
    centre{Vec3f{centreX,centreY,centreZ}},
    radius{R},
    colour{Colour{1,1,1}},
    wireframe(true),
    stacks(24),
    slices(24)
{
    initVAO();
}

Sphere::Sphere(const Sphere& other) noexcept
   :centre{other.Centre()},
    radius{other.Radius()},
    colour{other.getColour()},
    wireframe{other.Wireframe()},
    stacks(24),
    slices(24)
{
    initVAO();
}

Sphere::Sphere(Sphere&& other) noexcept
    :centre{other.Centre()},
     radius{other.Radius()},
     colour{other.getColour()},
     wireframe{other.Wireframe()},
     stacks(other.Stacks()),
     slices(other.Slices()),
     VAO(other.VAO)
{}

Sphere& Sphere::operator=(const Sphere& other) noexcept
{
    colour = other.getColour();
    radius = other.Radius();
    centre = other.Centre();
    wireframe = other.Wireframe();
    stacks = other.Stacks();
    slices = other.Slices();
    VAO = other.VAO;
    return *this;
}

Sphere& Sphere::operator=(Sphere&& other) noexcept
{
    colour = other.getColour();
    radius = other.Radius();
    centre = other.Centre();
    wireframe = other.Wireframe();
    stacks = other.Stacks();
    slices = other.Slices();
    VAO = other.VAO;

    return *this;
}


void Sphere::setPos(float X, float Y, float Z) noexcept
{
    centre = Vec3f(X,Y,Z);
}

void Sphere::setPos(const Vec3f& pos) noexcept
{
    centre = pos;
}

void Sphere::setColour(float R, float G, float B) noexcept
{
    colour = Colour{R,G,B};
}

void Sphere::setWireframe(bool b) noexcept
{
    wireframe = b;
}

void Sphere::setColour(const Vec3f& c) noexcept
{
    colour = Colour(c.R(),c.G(),c.B());
}

void Sphere::setColour(const Colour &c) noexcept
{
    colour = c;
}

void Sphere::setRadius(float R) noexcept
{
    radius = R;
}

bool Sphere::collides(const Sphere& other) const noexcept
{
    return (    (radius+other.Radius())*(radius+other.Radius()) >=
                ( (centre.X()-other.Centre().X())*(centre.X()-other.Centre().X()) +
                  (centre.Y()-other.Centre().Y())*(centre.Y()-other.Centre().Y()) +
                  (centre.Z()-other.Centre().Z())*(centre.Z()-other.Centre().Z()) )  );
}

void Sphere::initVAO()
{
    if(VAO != nullptr)
    {
        return;
    }
    VertexBuffer verts;
    ElementBuffer points;
    ElementBuffer tris;
    ElementBuffer wire;
    unsigned int idx = 0;
    for(size_t lat = 0; lat < stacks; lat++)
    {
        float V   = lat / (float) stacks;
        float phi = V * WrpDrv::Pi;
        for(size_t lon = 0; lon < slices; lon++)
        {
            float U = lon / (float) slices;
            float theta = U * (WrpDrv::Pi * 2);

            float x = std::cos(theta) * std::sin(phi);
            float y = std::cos(phi);
            float z = std::sin(theta) * std::sin(phi);

            Vec3f pos(x,y,z);
            Vec3f normal = centre - pos;

            verts.push_back(Vertex(pos,normal,Vec2f(lon/slices,lat/stacks),colour));
            points.push_back(idx++);
        }
    }

    // Calc The Index Positions
    for (int i = 0; i < slices * stacks + slices; ++i){

        tris.push_back (i);
        tris.push_back (i + slices + 1);
        tris.push_back (i + slices);

        tris.push_back (i + slices + 1);
        tris.push_back (i);
        tris.push_back (i + 1);
    }
    idx = 0;
    for(size_t Y = 0; Y < stacks - 1; Y ++)
    {
        for(size_t X = 0; X < slices; X++)
        {
            idx = Y*slices + X;
            wire.push_back(idx);
            wire.push_back(idx + slices);

            wire.push_back(idx);
            if(X < slices -1)
            {
                wire.push_back(idx+1);
            }
            else
            {
                wire.push_back(idx - X);
            }
        }
    }

    tris.setPrimitive(ElementBuffer::DrawType::TRIS);
    tris.Info().setName("Tris");
    points.setPrimitive(ElementBuffer::DrawType::POINTS);
    points.Info().setName("Points");
    wire.setPrimitive(ElementBuffer::DrawType::LINES);
    wire.Info().setName("Wire");
    VAO = std::make_shared<VertexArray>();
    VAO->pushElementBuffer(std::move(points));
    VAO->pushElementBuffer(std::move(tris));
    VAO->pushElementBuffer(std::move(wire));
    VAO->Verts(std::move(verts));
    VAO->Load();

}

void Sphere::draw() const noexcept
{

    Matrix44 model;
    model.setTranslation(centre.X(),centre.Y(),centre.Z());
    Matrix44 transform;
    transform.setScaling(radius);
//    Vec3f vec = crossProd(Vec3f{nX,nY,nZ}, Vec3f(0,1,0));
//    float angle = dotProd(Vec3f{nX,nY,nZ}, Vec3f(0,1,0));
//    transform.setRotationRad(angle,vec,false);

    glUniformMatrix4fv(transformUniform, 1, GL_FALSE, transform.Elements().data() );
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, model.Elements().data() );
    glUniform4f(ambientUniform, colour.R(), colour.G(), colour.B(), colour.A() );


    VAO->draw("Wire",true);

}


