#ifndef TIMED_MOVE_EVENT_H
#define TIMED_MOVE_EVENT_H

#include "ObjectEvent.h"
#include "DisplayManager.h"
#include "Vec3.h"

class TimedMoveEvent: public GOEvent
{
public:

	TimedMoveEvent(float Time = 0, const Vec3f& Distance = Vec3f(0,0,0) ) { time = Time; dist = Distance; vel = dist/time;}
	~TimedMoveEvent() {}

	void Update(GameObject* target);



protected:

	float time;
	Vec3f dist;
	Vec3f vel;


};




#endif //TIMED_MOVE_EVENT_H