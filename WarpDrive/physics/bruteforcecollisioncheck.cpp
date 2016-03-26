#include "bruteforcecollisioncheck.hpp"

BruteForceCheck::BruteForceCheck()
{

}

void BruteForceCheck::update(Game::iterator it)
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
        auto r0 = obj->BoundingSphere().Radius();
        auto p0 = obj->BoundingSphere().Centre();
        while(rest.next())
        {
            auto r1 = rest->BoundingSphere().Radius();
            auto p1 = rest->BoundingSphere().Centre();
            auto dist = p1 - p0;
            if(dist.sqMod() <= ((r0+r1)*(r0+r1)))
            {
                handlers.at(CollisionPair(obj->Type(), rest->Type()))(obj,rest);
            }
        }
    }
    while(it.next());
}
