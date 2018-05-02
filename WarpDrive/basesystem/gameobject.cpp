#include "WarpDrive/basesystem/gameobject.hpp"

#include "WarpDrive/basesystem/game.hpp"
#include "WarpDrive/basesystem/util.hpp"

void GameObject::update()
{
    for(std::vector<GOEvent*>::iterator it = events.begin(); it != events.end(); it++)
    {
        if(!( (*it)->Finished()))
        {
            (*it)->update(this);
        }
    }
    auto dt = DisplayManager::instance()->Dt();
    vel+= accel*(dt*0.001f);
    pos+= vel*(dt*0.001f);
}

GameObject::GameObject()
   :index{Game::instance()->ObjIndex()},
    vel{Vec3f(0,0,0)},
    pos{Vec3f(0,0,0)},
    accel{Vec3f(0,0,0)},
    mass{-1.f},
    radius{0},
    dimensions{Vec3f(0,0,0)},
    name{""},
    type{"Object"},
    events{},
    removeMe{false},
    modelUniform{-1},
    transformUniform{-1}
{}

AABBox GameObject::BoundingBox() const noexcept
{
    if(dimensions != Vec3f (0,0,0))
    {
        return AABBox( pos.X() - dimensions.X()/2, pos.X() + dimensions.X()/2 ,
                       pos.Y() - dimensions.Y()/2, pos.Y() + dimensions.Y()/2 ,
                       pos.Z() - dimensions.Z()/2, pos.Z() + dimensions.Z()/2 );
    }
    if(WrpDrv::flEquals(radius, 0.f))
    {
        return AABBox( pos.X() - radius, pos.X() + radius ,
                       pos.Y() - radius, pos.Y() + radius ,
                       pos.Z() - radius, pos.Z() + radius );
    }
    return AABBox();
}

Sphere GameObject::BoundingSphere() const noexcept
{
    return Sphere(pos, radius);
}
