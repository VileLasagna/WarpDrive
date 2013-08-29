#include "TimedRemoveEvent.h"
#include "DisplayManager.h"

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

