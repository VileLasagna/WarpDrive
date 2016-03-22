#include "events/panandtiltevent.hpp"
#include "display/camera.hpp"
#include "basesystem/displaymanager.hpp"


PanAndTiltEvent::PanAndTiltEvent(float Time, Vec3f Pan, Vec3f Tilt)
{
	pan = Pan;
	tilt = Tilt;
	time = Time;
    if (!WrpDrv::flEquals(time, 0.f))
	{
		overTime = true;
		panNudge = pan/time;
		tiltNudge = tilt/time;
	}
	else
	{
		overTime = false;
	}
}

void PanAndTiltEvent::update(GameObject* Target)
{
	if ( finished || (!Target) )
	{
		return;
	}
	Camera* C = dynamic_cast<Camera*> (Target);
	if( (Target && (!C)) )
	{
		Err::Notify("PandAndTiltEvent not attached to a Camera");
	}
	if(overTime)
	{
		float dt = DisplayManager::instance()->getDtSecs();
		time -= dt;
		if (pan != Vec3f(0,0,0))
		{
			C->setPos(C->Position() + ( panNudge*dt));
		}
		if(tilt != Vec3f(0,0,0))
		{
			std::pair<bool, Vec3f> currentTarget = C->Target();
			if(currentTarget.first)
			{
                C->setTarget(nullptr);
			}
			C->setTarget(currentTarget.second + (tiltNudge*dt));
		}
		if (time<= 0)
		{
			finished = true;
		}
	}
	else
	{
		C->setPos(C->Position() + pan);
		C->setTarget((C->Target().second)+tilt);
			//a little trick because there's no camera updates between these two calls
        C->setTarget(nullptr);
		finished = true;
	}
}



	
