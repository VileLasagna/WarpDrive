#ifndef BRUTEFORCECOLLISION_HPP
#define BRUTEFORCECOLLISION_HPP

#include "physics/collisionsystem.hpp"


class BruteForceCollision : public CollisionSystem
{
public:

    BruteForceCollision();


    // CollisionSystem interface
public:
    void Update(Game::iterator it);
};

#endif // BRUTEFORCECOLLISION_HPP
