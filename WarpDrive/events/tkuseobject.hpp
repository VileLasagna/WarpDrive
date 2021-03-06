#ifndef WD_TIMELINE_KEY_USE_OBJECT_HPP_DEFINED
#define WD_TIMELINE_KEY_USE_OBJECT_HPP_DEFINED

#include "WarpDrive/events/timelinekey.hpp"
#include "WarpDrive/basesystem/game.hpp"

#include <set>

class TKUseObject: public TimelineKey
{
public:

    TKUseObject(float Time = -0.01f, bool Activate = true, bool Draw = true, const std::string& Obj = "", bool isUniqueName = false);
    ~TKUseObject(){}
    void trigger();

protected:

    bool update;
    bool draw;
    bool unique;
    std::set<std::string> s;
    Game::iterator t; //for unique objects

};

#endif //WD_TIMELINE_KEY_USE_OBJECT_HPP_DEFINED
