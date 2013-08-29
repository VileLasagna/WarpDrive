#ifndef TIMED_REMOVE_EVENT_H
#define TIMED_REMOVE_EVENT_H

#include "ObjectEvent.h"
#include "GameObject.h"

class TimedRemoveEvent:public GOEvent
{

public:

	TimedRemoveEvent(float Time = 5);
	~TimedRemoveEvent(){}
	void Update(GameObject* target);

private:

	float time;
};





#endif //TIMED_REMOVE_EVENT_H