#ifndef WD_TIMED_MOVE_EVENT_HPP_DEFINED
#define WD_TIMED_MOVE_EVENT_HPP_DEFINED

#include "events/objectevent.hpp"
#include "basesystem/displaymanager.hpp"
#include "basemaths/vec3.hpp"

class TimedMoveEvent: public GOEvent
{

public:

	TimedMoveEvent(float Time = 0, const Vec3f& Distance = Vec3f(0,0,0) ) { time = Time; dist = Distance; vel = dist/time;}
	~TimedMoveEvent() {}

    void update(GameObject* target) override;

protected:

	float time;
	Vec3f dist;
	Vec3f vel;


};

#endif //WD_TIMED_MOVE_EVENT_HPP_DEFINED
