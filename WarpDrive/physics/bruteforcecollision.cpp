#include "bruteforcecollision.hpp"

BruteForceCollision::BruteForceCollision()
{

}

void BruteForceCollision::Update(Game::iterator it)
{
    if(it.isEmpty())
    {
        return;
    }
    GameObject* obj;
    do
    {
        obj = it;
        auto rest = it;
        auto r0 = obj->getSphere().Radius();
        auto p0 = obj->getSphere().Centre();
        while(rest.Next())
        {
            auto r1 = rest->getSphere().Radius();
            auto p1 = rest->getSphere().Centre();
            auto dist = p1 - p0;
            if(dist.sqMod() <= ((r0+r1)*(r0+r1)))
            {
                handlers.at(CollisionPair(obj->getType(), rest->getType()))(obj,rest);
            }
        }
    }
    while(it.Next());
}
