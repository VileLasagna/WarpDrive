#include "WarpDrive/events/timedremoveevent.hpp"
#include "WarpDrive/basesystem/displaymanager.hpp"

TimedRemoveEvent::TimedRemoveEvent(int64_t Time)
{
	time = Time;
}


void TimedRemoveEvent::update(GameObject* target)
{
    time -= DisplayManager::instance()->Dt();
    if (time <= 0 && (target != nullptr) )
	{
		target->KILL();
	}
}

