#ifndef TK_SET_DRAWN_OBJECTS_H
#define TK_SET_DRAWN_OBJECTS_H


#include "basesystem/game.hpp"
#include "events/timelinekey.hpp"


class TKDrawTeapot: public TimelineKey
{
public:
	TKDrawTeapot(){time = 5;}
	TKDrawTeapot(float Time){time = Time;}
	void Trigger()
	{
		std::set<std::string> drawntypes;
		drawntypes.insert("Teapot");
		Game::instance()->setDrawnTypes(drawntypes);
		Game::instance()->setActiveTypes(drawntypes);
	}

};

#endif TK_SET_DRAWN_OBJECTS_H
