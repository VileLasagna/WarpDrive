#ifndef WD_PAN_AND_TILT_EVENT_HPP_DEFINED
#define WD_PAN_AND_TILT_EVENT_HPP_DEFINED

#include "events/objectevent.hpp"
#include "basemaths/vec3.hpp"

class PanAndTiltEvent: public GOEvent
{

public:

	PanAndTiltEvent(float Time = 0, Vec3f Pan = Vec3f(), Vec3f Tilt = Vec3f());
	void update(GameObject* target);

protected:

	Vec3f pan, tilt, panNudge, tiltNudge;
	float time;
	bool overTime;

};

#endif //WD_PAN_AND_TILT_EVENT_HPP_DEFINED
