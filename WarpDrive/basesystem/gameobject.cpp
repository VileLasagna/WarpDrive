#include "basesystem/gameobject.hpp"


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
