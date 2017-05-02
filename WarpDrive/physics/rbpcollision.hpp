#ifndef RBPCOLLISION_HPP
#define RBPCOLLISION_HPP

#include "WarpDrive/basesystem/gameobject.hpp"

/**
 * @brief Class for simulating simple Rigid Body Physics
 */
class RBPcollision
{
public:

    RBPcollision();

    void operator()(GameObject* o1, GameObject* o2);

};

#endif // RBPCOLLISION_HPP
