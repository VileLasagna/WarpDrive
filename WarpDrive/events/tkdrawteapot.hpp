#ifndef WD_TK_SET_DRAWN_OBJECTS_HPP_DEFINED
#define WD_TK_SET_DRAWN_OBJECTS_HPP_DEFINED

#include "basesystem/game.hpp"
#include "events/timelinekey.hpp"


class TKDrawTeapot: public TimelineKey
{
public:
	TKDrawTeapot(){time = 5;}
	TKDrawTeapot(float Time){time = Time;}
	void trigger()
	{
		std::set<std::string> drawntypes;
		drawntypes.insert("Teapot");
		Game::instance()->setDrawnTypes(drawntypes);
		Game::instance()->setActiveTypes(drawntypes);
	}

};

#endif //WD_TK_SET_DRAWN_OBJECTS_HPP_DEFINED
