//#ifndef BOUNDING_BOX_H
//#define BOUNDING_BOX_H
//
//
//#include "Rect.h"
//
//
//template <class T>
//class BoundingBox: public Rect
//{
//
//public:
//	
//	BoundingBox () : mX(0), MX(0), mY(0), MY(0), mZ(0), MZ(0) {}
//	BoundingBox (T minX, T maxX, T minY, T maxY, T minZ, T maxZ) :  mX(minX), MX(maxX), mY(minY), MY(maxY), mZ(minZ), MZ(maxZ) {}
//	BoundingBox(const& Rect<T> ref) : mX(ref.minX), MX(ref.maxX), mY(ref.minY), MY (ref.maxY), mZ(0), MZ(0) {}
//
//	T minZ() const {return mZ;}
//	T maxZ() const {return MZ;}
//
//	T depth() const {return MZ-mz;}
//
//
//private:
//	T mZ, MZ;
//
//};
//
//
//#endif //BOUNDING_BOX_H
#ifndef BBOX_H
#define BBOX_H

#include "Vec3.h"
#include "Capsule.h"

class BBox
{
public:
  BBox(
    float xmin = 1000.0f, 
    float xmax = -1000.0f, 
    float ymin = 1000.0f, 
    float ymax = -1000.0f, 
    float zmin = 1000.0f, 
    float zmax = -1000.0f);

  void Set(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
  
  // Set values which are lower than the mins or greater than maxes.
  // I.e. enlarge the box to contain (x, y, z) if necessary.
  void SetIf(float x, float y, float z);

  void Draw() const;

  // Make an octree child.
  // Create a box which is 1/8 the volume of this box. The octant
  // parameter specifies the position of the sub-box within this one.
  // Valid values for octant are 0..7 incl.
  BBox MakeOctChild(int octant) const;

  // Returns true if the given vertex is inside this box.
  bool Contains(const Vec3f& v) const;

  float MinX() const { return m_xmin; }
  float MaxX() const { return m_xmax; }
  float MinY() const { return m_ymin; }
  float MaxY() const { return m_ymax; }
  float MinZ() const { return m_zmin; }
  float MaxZ() const { return m_zmax; }

private:
  float m_xmin, m_xmax, m_ymin, m_ymax, m_zmin, m_zmax;
};

bool Intersects(const Capsule& c, const BBox& box);

#endif
