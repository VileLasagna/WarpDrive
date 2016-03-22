
#include "events/glcolorevent.hpp"
#include "basesystem/displaymanager.hpp"

glColorEvent::glColorEvent(float Time, float Red, float Green, float Blue)
{
	time = Time;
	r = Red;
	g = Green;
	b = Blue;
	float rgb[4];
	glGetFloatv(GL_CURRENT_COLOR,rgb);
	r0 = rgb[0];
	g0 = rgb[1];
	b0 = rgb[2];
    if(!WrpDrv::flEquals(time, 0.f))
	{
		rStep = (r - r0)/time;
		gStep = (g - g0)/time;
		bStep = (b - b0)/time;
	}
}

void glColorEvent::update(GameObject* )
{
	if(finished)
	{
		return;
	}
    if (time <= 0)
	{
		glColor3f(r,g,b);
		finished = true;
	}
	else
	{
		float dt = DisplayManager::instance()->DtSecs();
		float rgb[4];
		glGetFloatv(GL_CURRENT_COLOR,rgb);
		r0 = rgb[0];
		g0 = rgb[1];
		b0 = rgb[2];
		glColor3f((r0+rStep*dt),(g0+gStep*dt),(b0+bStep*dt));
		time -= dt;
		if (time <= 0)
		{
			finished = true;
		}
	}

}
