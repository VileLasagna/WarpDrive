#ifndef WD_ALIGNEDBBOX_HPP_DEFINED
#define WD_ALIGNEDBBOX_HPP_DEFINED

#include "basemaths/vec3.hpp"
#include "basemaths/capsule.hpp"

class AABBox
{

public:

    AABBox( float x_min =  1000.0f  ,
            float x_max = -1000.0f  ,
            float y_min =  1000.0f  ,
            float y_max = -1000.0f  ,
            float z_min =  1000.0f  ,
            float z_max = -1000.0f  );

    void setBounds(float newxmin, float newxmax, float newymin, float newymax, float newzmin, float newzmax);

    // Set values which are lower than the mins or greater than maxes.
    // I.e. enlarge the box to contain (x, y, z) if necessary.
    void ensureContains(float x, float y, float z) noexcept;

    void draw() const;

    // Make an octree child.
    // Create a box which is 1/8 the volume of this box. The octant
    // parameter specifies the position of the sub-box within this one.
    // Valid values for octant are 0..7 incl.
    AABBox makeOctChild(int octant) const;

    // Returns true if the given vertex is inside this box.
    bool contains(const Vec3f& v) const noexcept;

    float MinX() const noexcept { return xmin; }
    float MaxX() const noexcept { return xmax; }
    float MinY() const noexcept { return ymin; }
    float MaxY() const noexcept { return ymax; }
    float MinZ() const noexcept { return zmin; }
    float MaxZ() const noexcept { return zmax; }

private:

    float xmin, xmax, ymin, ymax, zmin, zmax;

};

bool intersects(const Capsule& c, const AABBox& box);

#endif //WD_ALIGNEDBBOX_HPP_DEFINED
