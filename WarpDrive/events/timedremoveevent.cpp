#include "events/timedremoveevent.hpp"
#include "basesystem/displaymanager.hpp"

TimedRemoveEvent::TimedRemoveEvent(float Time)
{
	time = Time;
}


void TimedRemoveEvent::update(GameObject* target)
{
	time -= DisplayManager::instance()->DtSecs();
	if (time <= 0 && target)
	{
		target->KILL();
	}
}

