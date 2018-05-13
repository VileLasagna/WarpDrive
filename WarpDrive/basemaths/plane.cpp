#include "WarpDrive/basemaths/plane.hpp"

#ifdef WIN32
    #include <Windows.h>
#endif //WIN32

#include <GL/glew.h>
#include "WarpDrive/basemaths/matrix44.hpp"
#include "WarpDrive/basemaths/quaternion.hpp"

Plane::Plane()
{
    nX = 0;
    nY = 0;
    nZ = 0;
    d = 0;
    drawnCells = std::pair<int,int>(2,2);
    cellSize = 1;
    colour = Vec3f(0,1,0);
    drawWire = true;
    origin = Vec3f();
    d0 = d;
    showNormal = 0;
    tex = nullptr;
}

Plane::Plane (float A, float B, float C, float D)
{
    float sqmod = A*A+B*B+C*C;
    if(sqmod > 1.00001 || sqmod < 0.999999)
    {
        float mod = static_cast<float>(sqrt(sqmod));
        A /= mod;
        B /= mod;
        C /= mod;
    }
    nX = A;
    nY = B;
    nZ = C;
    d = D;
    drawnCells = std::pair<int,int>(2,2);
    cellSize = 1;
    colour = Vec3f(0,1,0);
    drawWire = true;
    origin = Vec3f(nX*D,nY*D,nZ*D);
    d0 = D;
    showNormal = false;
    tex = nullptr;
}

void Plane::useTexture(WDTexture *t, bool Tile)
{
    tex = t;
    tile = Tile;
}

Plane::Plane (const Vec3f& Normal, float Distance)
{
    nX = Normal.X();
    nY = Normal.Y();
    nZ = Normal.Z();
    d = Distance;
    drawnCells = std::pair<int,int>(2,2);
    cellSize = 1;
    colour = Vec3f(0,1,0);
    drawWire = true;
    origin = Vec3f(nX*d,nY*d,nZ*d);
    d0 = d;
    showNormal = false;
    tex = nullptr;
}

Plane::Plane (const Vec3f& P1, const Vec3f& P2, const Vec3f& P3)
{
    Vec3f N = triNormal(P1,P2,P3);
    nX = N.X();
    nY = N.Y();
    nZ = N.Z();
    d = dotProd(P1, N);
    drawnCells = std::pair<int,int>(2,2);
    cellSize = 1;
    drawWire = true;
    origin = Vec3f(nX*d,nY*d,nZ*d);
    d0 = d;
    showNormal = false;
    tex = 0;
}

void Plane::setNormal(const Vec3f& N)
{
    //This function is for "rotating" the plane around the origin of the WORLD
    float M = N.sqMod();
    if(M > 1.0000001 || M < 0.9999999)
        //check if N is normalised and do so if it isn't.
    {
        Vec3f norm = N;
        norm.normalise();
        nX = norm.X();
        nY = norm.Y();
        nZ = norm.Z();
    }
    else
    {
        nX = N.X();
        nY = N.Y();
        nZ = N.Z();
    }
}

void Plane::rotateAroundOrigin(const Vec3f &angles)
{
    Matrix44 rot;
    rot.setRotation(angles.X(), angles.Y(), angles.Z());
    Vec3f newNorm = Vec3f(nX,nY,nZ);
    newNorm = (Matrix44::multiply(rot,Vec4f(newNorm))).toVec3();
    Vec3f Norm = newNorm;
    d = d0*dotProd(Norm,newNorm);
    nX = newNorm.X();
    nY = newNorm.Y();
    nZ = newNorm.Z();

}

void Plane::drawAsWireframe(bool b) noexcept
{
    drawWire = b;
}

void Plane::setDrawn(int X, int Y, float size)
{
    VertexBuffer vertices;

    size = std::abs(size);
    drawnCells.first = X;
    drawnCells.second = Y;
    cellSize = size;

    ElementBuffer::Data faceIndexes;
    ElementBuffer::Data wireIndexes;

    Vec2f mins(size*X, size*Y);
    mins *= -0.5f;


    vertices.push_back(Vertex(Vec3f(0, 0, 0),
                              Vec3f(0,1,0),
                              Vec2f(0, 0),
                              colour,
                              Colour(1,1,1),
                              Colour(1,1,1),
                              -1.f ) );

    vertices.push_back(Vertex(Vec3f(0, size, 0),
                              Vec3f(0,1,0),
                              Vec2f(0,0),
                              colour,
                              Colour(1,1,1),
                              Colour(1,1,1),
                              -1.f ) );

    ElementBuffer::Data normalIndexes{0,1};

    //(Row+1) * (column+1) total vertices
    for(size_t row = 0; row <= X; row ++)
    {
        for(size_t col = 0; col <= Y; col ++)
        {
            vertices.push_back(Vertex(Vec3f(mins.X() + size*row, 0, mins.Y() + size*col),
                                      Vec3f(0,1,0),
                                      Vec2f(row*(1/X), col*(1/Y)),
                                      colour,
                                      Colour(1,1,1),
                                      Colour(1,1,1),
                                      -1.f ) );

        }
    }

    for(size_t row = 0; row <= X; row ++)
    {

            wireIndexes.push_back((row*(X+1))+2);
            wireIndexes.push_back(((row*(X+1)) + Y)+2);

    }

    for(size_t col = 0; col <= Y; col ++)
    {
        wireIndexes.push_back( (col)+2);
        wireIndexes.push_back( ( (Y*(X+1)) + col) + 2 );
    }

    for(size_t row = 0; row < X; row++)
    {
        for(size_t col = 0; col < Y; col++)
        {
            unsigned int idx = ((row*(X+1)) + col) +2;
            unsigned int stride = (X+1);
            faceIndexes.push_back(idx);
            faceIndexes.push_back(idx+1);
            faceIndexes.push_back(idx+1+stride);

            faceIndexes.push_back(idx);
            faceIndexes.push_back(idx+1+stride);
            faceIndexes.push_back(idx+stride);

        }
    }


    ElementBuffer normalBuffer(ElementBuffer::DrawType::LINES, normalIndexes, "Normal");
    ElementBuffer wireframe(ElementBuffer::DrawType::LINES, wireIndexes, "Wireframe");
    ElementBuffer Faces(ElementBuffer::DrawType::TRIS, faceIndexes, "Faces");
    VAO.pushElementBuffer(std::move(normalBuffer));
    VAO.pushElementBuffer(std::move(wireframe));
    VAO.pushElementBuffer(std::move(Faces));
//    VAO.setPrimitives(VertexArray::DrawType::POINTS);
    VAO.Verts(std::move(vertices));
    VAO.Load();
}

void Plane::setColour(const Vec3f& rgb) noexcept
{
    colour = rgb;
}

void Plane::setColour(float r, float g, float b) noexcept
{
    colour = Vec4f(r,g,b,1);
}

void Plane::setColour(const Vec4f& rgba) noexcept
{
    colour = rgba;
}

void Plane::setColour(float r, float g, float b, float a) noexcept
{
    colour = Vec4f(r,g,b,a);
}
void Plane::setColour(const Colour& c) noexcept
{
    colour = c;
}


void Plane::drawNormal(bool b) noexcept
{
    showNormal = b;

}
void Plane::draw() const noexcept
{
    Matrix44 model;
    model.setTranslation(origin.X(),origin.Y(),origin.Z());
    Matrix44 transform;
//    Vec3f vec = crossProd(Vec3f{nX,nY,nZ}, Vec3f(0,1,0));
//    float angle = dotProd(Vec3f{nX,nY,nZ}, Vec3f(0,1,0));
//    transform.setRotationRad(angle,vec,false);

    glUniformMatrix4fv(transformUniform, 1, GL_FALSE, transform.Elements().data() );
    glUniformMatrix4fv(modelUniform, 1, GL_FALSE, model.Elements().data() );


    if(drawWire)
    {
        VAO.draw("Wireframe");
    }
    else
    {
        VAO.draw("Faces");
    }

    if(showNormal)
    {
        VAO.draw("Normal");
    }


}
