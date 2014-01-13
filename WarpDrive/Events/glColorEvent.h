#ifndef GL_COLOR_EVENT_H
#define GL_COLOR_EVENT_H

#include "ObjectEvent.h"

class glColorEvent: public GOEvent
{
/* This class represents an event that sets an object to change colour, through its material, over time
*/
public:

	glColorEvent(float Time = 0, float Red = 1, float Green = 1, float Blue = 1);
	~glColorEvent(){}
	void Update(GameObject* target);

private:

	float time, R, G, B, R0,G0,B0, Rstep, Gstep, Bstep;

};



#endif //GL_COLOR_EVENT_H