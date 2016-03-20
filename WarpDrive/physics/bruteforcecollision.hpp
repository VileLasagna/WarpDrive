#ifndef WD_BRUTEFORCECOLLISION_HPP_DEFINED
#define WD_BRUTEFORCECOLLISION_HPP_DEFINED

#include "physics/collisionsystem.hpp"

class BruteForceCollision : public CollisionSystem
{

public:

    BruteForceCollision();

    // CollisionSystem interface
public:

    void update(Game::iterator it);
};

#endif // WD_BRUTEFORCECOLLISION_HPP_DEFINED
