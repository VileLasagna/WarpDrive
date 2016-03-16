#include "basesystem/gameobject.hpp"
#include "basesystem/game.hpp"


void GameObject::Update()
{
	for(std::vector<GOEvent*>::iterator it = events.begin(); it != events.end(); it++)
	{
        if(!( (*it)->isFinished()))
        {
            (*it)->Update(this);
        }
	}
	float dt = DisplayManager::instance()->getDtSecs();
	vel+= accel*dt;
	pos+= vel*dt;
}

GameObject::GameObject()
{
    index = Game::instance()->ObjIndex();
}

AABBox GameObject::getBox() const noexcept
{
    if(dimensions != Vec3f (0,0,0))
    {
        return AABBox( pos.X() - dimensions.X()/2, pos.X() + dimensions.X()/2 ,
                       pos.Y() - dimensions.Y()/2, pos.Y() + dimensions.Y()/2 ,
                       pos.Z() - dimensions.Z()/2, pos.Z() + dimensions.Z()/2 );
    }
    if(radius != 0)
    {
        return AABBox( pos.X() - radius, pos.X() + radius ,
                       pos.Y() - radius, pos.Y() + radius ,
                       pos.Z() - radius, pos.Z() + radius );
    }
    return AABBox();
}

Sphere GameObject::getSphere() const noexcept
{
    return Sphere(pos, radius);
}
