#ifndef OCTREE_H
#define OCTREE_H

#include <vector>
#include "BaseMaths/Tri.hpp"
#include "Physics/AlignedBoundingBox.hpp"

class OctreeLeaf;


class Octree
{
public:
    virtual ~Octree() {}
    virtual void Draw() = 0;
	virtual void getIntersectingLeaves(const Capsule& capsule, std::vector<OctreeLeaf*>* pLeaves) = 0;


protected:
    // Every concrete Octree type needs a bounding box
    BBox box;
};

class OctreeLeaf : public Octree
{
public:
	OctreeLeaf(const std::vector<Tri>& tris, const BBox& box);
	virtual void getIntersectingLeaves(const Capsule& capsule, std::vector<OctreeLeaf*>* pLeaves);

    virtual void Draw();

private:
	std::vector<Tri> tris;
};

class OctreeComposite : public Octree
{
public:
    OctreeComposite(const BBox& box);

	virtual void getIntersectingLeaves(const Capsule& capsule, std::vector<OctreeLeaf*>* pLeaves);

    virtual void Draw();
    void AddChild(Octree*);

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

#endif
