#ifndef WD_TIMED_REMOVE_EVENT_HPP_DEFINED
#define WD_TIMED_REMOVE_EVENT_HPP_DEFINED

#include "WarpDrive/events/objectevent.hpp"
#include "WarpDrive/basesystem/gameobject.hpp"

class TimedRemoveEvent:public GOEvent
{

public:

    TimedRemoveEvent(int64_t Time = 5);
    ~TimedRemoveEvent(){}
    void update(GameObject* target) override;

private:

    float time;
};

#endif //WD_TIMED_REMOVE_EVENT_HPP_DEFINED
