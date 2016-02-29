#ifndef TIMELINE_KEY_ADD_EVENT_H
#define TIMELINE_KEY_ADD_EVENT_H

#include "events/timelinekey.hpp"
#include "basesystem/gameobject.hpp"

class TKAddEvent: public TimelineKey
{
public:
	TKAddEvent(float Time = -0.01, GameObject* target = 0, GOEvent* e = 0) {time = Time; Object = target; Ev = e;}
	virtual ~TKAddEvent(){}
	void Trigger() {if(Object && Ev){Object->addEvent(Ev);}}

protected:

	GameObject* Object;
	GOEvent* Ev;
};





#endif //TIMELINE_KEY_ADD_EVENT_H
