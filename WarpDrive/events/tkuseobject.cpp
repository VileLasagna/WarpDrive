#include "tkuseobject.hpp"

TKUseObject::TKUseObject(float Time, bool Activate, bool Draw, const std::string& Obj, bool isUniqueName)
{

	time = Time;
	draw = Draw;
	update = Activate;
	S.insert(Obj);
	unique = isUniqueName;
	if (unique)
	{
		T = Game::iterator();
		T.seekName(Obj);
	}
}

void TKUseObject::Trigger()
{
	if(unique)
	{
		if(draw)
		{
			Game::instance()->addDrawnObject(T);
		}
		else
		{
			Game::instance()->removeDrawnObject(T);
		}
		if(update)
		{
			Game::instance()->addActiveObject(T);
		}
		else
		{
			Game::instance()->removeActiveObject(T);
		}
	}
	else
	{
		if(draw)
		{
			Game::instance()->addDrawnTypes(S);
		}
		else
		{
			Game::instance()->removeDrawnTypes(S);
		}
		if(update)
		{
			Game::instance()->removeActiveTypes(S);
		}
	}
}

