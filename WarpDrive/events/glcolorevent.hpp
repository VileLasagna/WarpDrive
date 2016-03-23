#ifndef WD_GL_COLOR_EVENT_HPP_DEFINED
#define WD_GL_COLOR_EVENT_HPP_DEFINED

#include <cstdint>

#include "events/objectevent.hpp"

class glColorEvent: public GOEvent
{
/* This class represents an event that sets an object to change colour, through its material, over time
*/
public:

    glColorEvent(int64_t Time = 0, float Red = 1, float Green = 1, float Blue = 1);
	~glColorEvent(){}
    void update(GameObject* target) override;

private:

    int64_t time;
    float r;
    float g;
    float b;
    float r0;
    float g0;
    float b0;
    float rStep;
    float gStep;
    float bStep;

};

#endif //WD_GL_COLOR_EVENT_HPP_DEFINED
