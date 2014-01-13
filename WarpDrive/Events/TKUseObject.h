#ifndef TIMELINE_KEY_USE_OBJECT_H
#define TIMELINE_KEY_USE_OBJECT_H

#include "Events/TimelineKey.h"
#include "BaseSystem/Game.h"

#include <set>

class TKUseObject: public TimelineKey
{
public:

	TKUseObject(float Time = -0.01, bool Activate = true, bool Draw = true, const std::string& Obj = "", bool isUniqueName = false);
	~TKUseObject(){}
	void Trigger();

protected:

	bool update,draw,unique;
	std::set<std::string> S;
	Game::iterator T; //for unique objects


};

#endif //TIMELINE_KEY_USE_OBJECT_H
