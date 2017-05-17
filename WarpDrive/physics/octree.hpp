#ifndef WD_OCTREE_HPP_DEFINED
#define WD_OCTREE_HPP_DEFINED

#include <vector>

#include "WarpDrive/basemaths/tri.hpp"
#include "WarpDrive/physics/alignedboundingbox.hpp"

class OctreeLeaf;

class Octree
{

public:

    virtual ~Octree() {}
    virtual void draw() = 0;
    virtual void IntersectingLeaves(const Capsule& capsule, std::vector<OctreeLeaf*>* pLeaves) = 0;


protected:
    // Every concrete Octree type needs a bounding box
    AABBox box;
};

class OctreeLeaf : public Octree
{

public:

    OctreeLeaf(const std::vector<Tri>& tris, const AABBox& box);
    virtual void IntersectingLeaves(const Capsule& capsule, std::vector<OctreeLeaf*>* pLeaves);

    virtual void draw();

private:

    std::vector<Tri> tris;
};

class OctreeComposite : public Octree
{

public:

    OctreeComposite(const AABBox& box);

    virtual void IntersectingLeaves(const Capsule& capsule, std::vector<OctreeLeaf*>* pLeaves);

    virtual void draw();
    void addChild(Octree*);

    ~OctreeComposite()
    {
        for(int i = 0; i < children.size(); i++)
        {
            delete children[i];
        }
    }

private:

    std::vector<Octree*> children;

};

#endif //WD_OCTREE_HPP_DEFINED
