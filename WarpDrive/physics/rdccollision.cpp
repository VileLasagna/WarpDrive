#include "rdccollision.hpp"

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

    RDC(Axis::X, Axis::Y, Axis::Z);

}

void RDCCollision::RDC(RDCCollision::Axis a1, RDCCollision::Axis a2, RDCCollision::Axis a3)
{

}

void RDCCollision::BruteForce(std::vector<GameObject*> group)
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
                handlers.at(CollisionPair(obj->getType(), other->getType()))(obj,other);
            }
        }
    }
    while(it.Next());
}
