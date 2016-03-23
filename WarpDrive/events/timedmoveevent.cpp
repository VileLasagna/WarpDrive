#include "events/timedmoveevent.hpp"
#include "basesystem/gameobject.hpp"
#include "basesystem/displaymanager.hpp"



void TimedMoveEvent::update(GameObject* target)
{
	if (time <= 0)
	{
		finished = true;
		return;
	}
    auto dt = DisplayManager::instance()->Dt();
	time -= dt;
    Vec3f nudge = vel*(dt*0.001f);
	target->setPos( nudge + (target->Position()) );

}
