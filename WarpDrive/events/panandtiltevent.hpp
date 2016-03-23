#ifndef WD_PAN_AND_TILT_EVENT_HPP_DEFINED
#define WD_PAN_AND_TILT_EVENT_HPP_DEFINED

#include <cstdint>

#include "events/objectevent.hpp"
#include "basemaths/vec3.hpp"

class PanAndTiltEvent: public GOEvent
{

public:

    PanAndTiltEvent(int64_t Time = 0, Vec3f Pan = Vec3f(), Vec3f Tilt = Vec3f());
	void update(GameObject* target);

protected:

	Vec3f pan, tilt, panNudge, tiltNudge;
    int64_t time;
	bool overTime;

};

#endif //WD_PAN_AND_TILT_EVENT_HPP_DEFINED
