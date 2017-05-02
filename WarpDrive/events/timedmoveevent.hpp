#ifndef WD_TIMED_MOVE_EVENT_HPP_DEFINED
#define WD_TIMED_MOVE_EVENT_HPP_DEFINED

#include "WarpDrive/events/objectevent.hpp"
#include "WarpDrive/basesystem/displaymanager.hpp"
#include "WarpDrive/basemaths/vec3.hpp"

class TimedMoveEvent: public GOEvent
{

public:

    TimedMoveEvent(int64_t Time = 0, const Vec3f& Distance = Vec3f(0,0,0) ) { time = Time; dist = Distance; vel = dist/static_cast<float>(time);}
	~TimedMoveEvent() {}

    void update(GameObject* target) override;

protected:

    int64_t time;
	Vec3f dist;
	Vec3f vel;


};

#endif //WD_TIMED_MOVE_EVENT_HPP_DEFINED
