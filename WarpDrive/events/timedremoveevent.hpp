#ifndef WD_TIMED_REMOVE_EVENT_HPP_DEFINED
#define WD_TIMED_REMOVE_EVENT_HPP_DEFINED

#include "events/objectevent.hpp"
#include "basesystem/gameobject.hpp"

class TimedRemoveEvent:public GOEvent
{

public:

	TimedRemoveEvent(float Time = 5);
	~TimedRemoveEvent(){}
    void update(GameObject* target) override;

private:

	float time;
};

#endif //WD_TIMED_REMOVE_EVENT_HPP_DEFINED
