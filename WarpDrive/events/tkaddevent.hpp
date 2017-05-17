#ifndef WD_TIMELINE_KEY_ADD_EVENT_HPP_DEFINED
#define WD_TIMELINE_KEY_ADD_EVENT_HPP_DEFINED

#include "WarpDrive/events/timelinekey.hpp"
#include "WarpDrive/basesystem/gameobject.hpp"

class TKAddEvent: public TimelineKey
{

public:

    TKAddEvent(float Time = -0.01, GameObject* target = 0, GOEvent* e = 0) {time = Time; object = target; ev = e;}
    virtual ~TKAddEvent(){}
    void trigger() {if(object && ev){object->addEvent(ev);}}

protected:

    GameObject* object;
    GOEvent* ev;
};

#endif //WD_TIMELINE_KEY_ADD_EVENT_HPP_DEFINED
