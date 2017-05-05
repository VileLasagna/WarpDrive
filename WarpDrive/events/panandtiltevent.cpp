#include "WarpDrive/events/panandtiltevent.hpp"
#include "WarpDrive/display/camera.hpp"
#include "WarpDrive/basesystem/displaymanager.hpp"


PanAndTiltEvent::PanAndTiltEvent(int64_t Time, Vec3f Pan, Vec3f Tilt)
{
	pan = Pan;
	tilt = Tilt;
	time = Time;
    if (time > 0)
	{
		overTime = true;
        panNudge = pan/static_cast<float>(time);
        tiltNudge = tilt/static_cast<float>(time);
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
        auto dt = DisplayManager::instance()->Dt();
		time -= dt;
		if (pan != Vec3f(0,0,0))
		{
            C->setPos(C->Position() + ( panNudge*static_cast<float>(dt)));
		}
		if(tilt != Vec3f(0,0,0))
		{
			std::pair<bool, Vec3f> currentTarget = C->Target();
			if(currentTarget.first)
			{
                C->setTarget(nullptr);
			}
            C->setTarget(currentTarget.second + (tiltNudge*static_cast<float>(dt)) );
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



	
