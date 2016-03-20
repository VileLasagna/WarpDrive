#include "physics/alignedboundingbox.hpp"
#include "basemaths/vec3.hpp"
#include "basemaths/cliplinesegbox.hpp"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include <GL/gl.h>


AABBox::AABBox( float x_min, float x_max,
                float y_min, float y_max,
                float z_min, float z_max )
   :xmin{x_min}, xmax{x_max},
    ymin{y_min}, ymax{y_max},
    zmin{z_min}, zmax{z_max}
{}

void AABBox::ensureContains(float x, float y, float z) noexcept
{
    xmin = xmin <= x ? xmin : x;
    xmax = xmax >= x ? xmax : x;
    ymin = ymin <= y ? ymin : y;
    ymax = ymax >= y ? ymax : y;
    zmin = zmin <= z ? zmin : z;
    zmax = zmax >= z ? zmax : z;
}

void DrawLine(const Vec3f& v1, const Vec3f& v2)
{
    glDisable(GL_TEXTURE_2D);
    glBegin(GL_LINES);
        glVertex3f(v1.X(), v1.Y(), v1.Z());
        glVertex3f(v2.X(), v2.Y(), v2.Z());
    glEnd();
    glEnable(GL_TEXTURE_2D);
}

void AABBox::draw() const
{
    DrawLine( Vec3f(xmin, ymin, zmin) ,
            Vec3f(xmax, ymin, zmin) );

    DrawLine( Vec3f(xmax, ymin, zmin) ,
            Vec3f(xmax, ymin, zmax) );

    DrawLine( Vec3f(xmax, ymin, zmax) ,
            Vec3f(xmin, ymin, zmax) );

    DrawLine( Vec3f(xmin, ymin, zmax) ,
            Vec3f(xmin, ymin, zmin) );

    DrawLine( Vec3f(xmin, ymax, zmin) ,
            Vec3f(xmax, ymax, zmin) );

    DrawLine( Vec3f(xmax, ymax, zmin) ,
            Vec3f(xmax, ymax, zmax) );

    DrawLine( Vec3f(xmax, ymax, zmax) ,
            Vec3f(xmin, ymax, zmax) );

    DrawLine( Vec3f(xmin, ymax, zmax) ,
            Vec3f(xmin, ymax, zmin) );

    DrawLine( Vec3f(xmin, ymin, zmin) ,
            Vec3f(xmin, ymax, zmin) );

    DrawLine( Vec3f(xmax, ymin, zmin) ,
            Vec3f(xmax, ymax, zmin) );

    DrawLine( Vec3f(xmax, ymin, zmax) ,
            Vec3f(xmax, ymax, zmax) );

    DrawLine( Vec3f(xmin, ymin, zmax) ,
            Vec3f(xmin, ymax, zmax) );
}

AABBox AABBox::makeOctChild(int octant) const
{
    // Centre of box
    float cx = (xmin + xmax) / 2.0f;
    float cy = (ymin + ymax) / 2.0f;
    float cz = (zmin + zmax) / 2.0f;

    float x_min = xmin, x_max = xmax, y_min = ymin, y_max = ymax, z_min = zmin, z_max = zmax;
    if (octant & 1)
    {
        x_min = cx;
    }
    else
    {
        x_max = cx;
    }
    if (octant & 2)
    {
        y_min = cy;
    }
    else
    {
        y_max = cy;
    }
    if (octant & 4)
    {
        z_min = cz;
    }
    else
    {
        z_max = cz;
    }

    return AABBox(x_min, x_max, y_min, y_max, z_min, z_max);
}

bool AABBox::contains(const Vec3f& v) const noexcept
{
    return (    v.X() >= xmin && v.X() < xmax &&
                v.Y() >= ymin && v.Y() < ymax &&
                v.Z() >= zmin && v.Z() < zmax );
}

bool intersects(const Capsule& c, const AABBox& box)
{
    AABBox B(box.MinX()-c.Radius(), box.MaxX() + c.Radius(), box.MinY()-c.Radius(), box.MaxY()+c.Radius(), box.MinZ() - c.Radius(), box.MaxZ() + c.Radius());
    LineSeg clipped = c.Path();
    return Clip(clipped,B);
}
