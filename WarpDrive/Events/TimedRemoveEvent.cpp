#include "Events/TimedRemoveEvent.hpp"
#include "BaseSystem/DisplayManager.hpp"

TimedRemoveEvent::TimedRemoveEvent(float Time)
{
	time = Time;
}


void TimedRemoveEvent::Update(GameObject* target)
{
	time -= DisplayManager::instance()->getDtSecs();
	if (time <= 0 && target)
	{
		target->KILL();
	}
}

