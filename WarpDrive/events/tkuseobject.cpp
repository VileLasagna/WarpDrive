#include "WarpDrive/events/tkuseobject.hpp"

TKUseObject::TKUseObject(float Time, bool Activate, bool Draw, const std::string& Obj, bool isUniqueName)
{

	time = Time;
	draw = Draw;
	update = Activate;
	s.insert(Obj);
	unique = isUniqueName;
	if (unique)
	{
		t = Game::iterator();
		t.seekName(Obj);
	}
}

void TKUseObject::trigger()
{
	if(unique)
	{
		if(draw)
		{
			Game::instance()->addDrawnObject(t);
		}
		else
		{
			Game::instance()->removeDrawnObject(t);
		}
		if(update)
		{
			Game::instance()->addActiveObject(t);
		}
		else
		{
			Game::instance()->removeActiveObject(t);
		}
	}
	else
	{
		if(draw)
		{
			Game::instance()->addDrawnTypes(s);
		}
		else
		{
			Game::instance()->removeDrawnTypes(s);
		}
		if(update)
		{
			Game::instance()->removeActiveTypes(s);
		}
	}
}

