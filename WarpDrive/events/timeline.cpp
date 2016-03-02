#include "basesystem/factory.hpp"
#include "events/timeline.hpp"
#include "basesystem/displaymanager.hpp"


Timeline::Timeline()
{

	time = 0;
	NextKey = keys.begin();
	lastAdded = 0;

}

void Timeline::Load(const std::string& )
{

	//load file here

}


void Timeline::Update()
{

	time += DisplayManager::instance()->getDtSecs();
	if(NextKey == keys.end())
	{
		return;
	}
	std::multiset<TimelineKey*,MyCompare>::iterator it = NextKey;
	while( it != keys.end() && time >= (*it)->getTime())
	{
		(*it)->Trigger();
		it++;
	}
	NextKey = it;

}

void Timeline::Reset()
{
	time = 0;
	NextKey = keys.begin();
}

void Timeline::addKey(TimelineKey *key)
{
	if(key->getTime() <= 0)
	{
		//If the key has a negative time value, interpret that as
		//positive time RELATIVE to the last added timeline key
		if(lastAdded)
		{
			float t = lastAdded->getTime() + std::abs(key->getTime());
			key->setTime(t);
		}
		else
		{
			key->setTime(0); //Defaults to 0;
		}
	}
	keys.insert(key);
	lastAdded = key;
	NextKey = keys.begin();
}

Timeline::~Timeline()
{
	for (std::multiset<TimelineKey*,MyCompare>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		delete (*it);
	}
	keys.clear();
}