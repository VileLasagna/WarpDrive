#ifndef WD_BRUTEFORCECOLLISION_HPP_DEFINED
#define WD_BRUTEFORCECOLLISION_HPP_DEFINED

#include "WarpDrive/physics/collisionsystem.hpp"

class BruteForceCheck : public CollisionSystem
{

public:

    BruteForceCheck();

    // CollisionSystem interface
public:

    void update(Game::iterator it);
};

#endif // WD_BRUTEFORCECOLLISION_HPP_DEFINED
