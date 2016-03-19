#include "rdccollision.hpp"

#include <algorithm>

RDCCollision::RDCCollision()
{

}

void RDCCollision::Update(Game::iterator it)
{
    pairs.clear();
    objs.clear();

    if(it.isEmpty())
    {
        return;
    }
    do
    {
        objs.push_back(it);
    }
    while(it.Next());

    RDC(Axis::X, Axis::Y, Axis::Z, objs);

    for(ObjPair p: pairs)
    {
        handlers.at(CollisionPair(p.first->getType(), p.second->getType()))(p.first,p.second);
    }

}

void RDCCollision::RDC(RDCCollision::Axis a1, RDCCollision::Axis a2, RDCCollision::Axis a3, std::vector<GameObject*> group)
{
    if(group.size() <= RDCLimit || a1 == Axis::NONE)
    {
        //end recursion
        BruteForce(group);
        return;
    }

    EdgeVec bounds {SortedBoundaries(a1, group)};

    std::vector <GameObject*> subGroup;
    Axis nextA1 {a2};
    Axis nextA2 {a3};
    Axis nextA3 {Axis::NONE};
    size_t count {0};
    bool subdivided = false;

    for(EdgeInfo edge: bounds)
    {
        if(edge.min)
        {
            //add to cluster
            count++;
            subGroup.push_back(edge.obj);
        }
        else
        {
            count--;
            if(count == 0)
            {
                //end of cluster. Recursive call
                if(edge != bounds.back())
                {
                    subdivided = true;
                }
                if(subdivided)
                {
                    switch(a1)
                    {
                        case Axis::X:
                            nextA1 = Axis::Y;
                            nextA2 = Axis::Z;
                            break;
                        case Axis::Y:
                            nextA1 = Axis::X;
                            nextA2 = Axis::Z;
                            break;
                        case Axis::Z:
                            nextA1 = Axis::X;
                            nextA2 = Axis::Z;
                            break;
                        case Axis::NONE:
                            assert(0);
                    }
                }
            }

            RDC(nextA1,nextA2,nextA3,subGroup);
            subGroup.clear();
        }
    }
}

void RDCCollision::BruteForce(std::vector<GameObject*> group) noexcept
{
    GameObject* obj;
    for(size_t i = 0; i < group.size(); i++)
    {
        obj = group[i];
        auto r0 = obj->getSphere().Radius();
        auto p0 = obj->getSphere().Centre();
        for(size_t j = i+1; j < group.size(); j++)
        {
            GameObject* other = group[j];
            auto r1 = other->getSphere().Radius();
            auto p1 = other->getSphere().Centre();
            auto dist = p1 - p0;
            if(dist.sqMod() <= ((r0+r1)*(r0+r1)))
            {
                //handlers.at(CollisionPair(obj->getType(), other->getType()))(obj,other);
                pairs.push_back(ObjPair(obj,other));
            }
        }
    }
}

RDCCollision::EdgeVec RDCCollision::SortedBoundaries(RDCCollision::Axis a, std::vector<GameObject*> objs) const
{
    EdgeVec edges;
    for(GameObject* o: objs)
    {
        EdgeInfo min;
        auto sizes = o->Dimensions();
        auto val = sizes.X();
        auto pos = o->getPos();
        auto centre = pos.X();
        if (a != RDCCollision::Axis::X)
        {
            if(a == RDCCollision::Axis::Y)
            {
                val = sizes.Y();
                centre = pos.Y();
            }
            else
            {
                val = sizes.Z();
                centre = pos.Y();
            }
        }
        min.obj = o;
        min.index = o->Index();
        min.min = true;
        min.value = centre - (val/2);

        EdgeInfo max(min);
        max.min = false;
        max.value += val;

        edges.push_back(min);
        edges.push_back(max);
    }

    std::sort(edges.begin(), edges.end());
    return edges;
}
