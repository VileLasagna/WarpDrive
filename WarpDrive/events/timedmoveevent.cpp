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
	float dt = DisplayManager::instance()->DtSecs();
	time -= dt;
	Vec3f nudge = vel*dt;
	target->setPos( nudge + (target->Position()) );

}
