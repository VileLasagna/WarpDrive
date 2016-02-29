
#include "events/glcolorevent.hpp"
#include "basesystem/displaymanager.hpp"

glColorEvent::glColorEvent(float Time, float Red, float Green, float Blue)
{
	time = Time;
	R = Red;
	G = Green;
	B = Blue;
	float rgb[4];
	glGetFloatv(GL_CURRENT_COLOR,rgb);
	R0 = rgb[0];
	G0 = rgb[1];
	B0 = rgb[2];
	if(time)
	{
		Rstep = (R - R0)/time;
		Gstep = (G - G0)/time;
		Bstep = (B - B0)/time;
	}
}

void glColorEvent::Update(GameObject* )
{
	if(finished)
	{
		return;
	}
	if (!time)
	{
		glColor3f(R,G,B);
		finished = true;
	}
	else
	{
		float dt = DisplayManager::instance()->getDtSecs();
		float rgb[4];
		glGetFloatv(GL_CURRENT_COLOR,rgb);
		R0 = rgb[0];
		G0 = rgb[1];
		B0 = rgb[2];
		glColor3f((R0+Rstep*dt),(G0+Gstep*dt),(B0+Bstep*dt));
		time -= dt;
		if (time <= 0)
		{
			finished = true;
		}
	}

}
