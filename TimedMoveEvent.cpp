#include "TimedMoveEvent.h"
#include "GameObject.h"
#include "DisplayManager.h"



void TimedMoveEvent::Update(GameObject* target)
{
	if (time <= 0)
	{
		finished = true;
		return;
	}
	float dt = DisplayManager::instance()->getDtSecs();
	time -= dt;
	Vec3f nudge = vel*dt;
	target->setPos( nudge + (target->getPos()) );

}