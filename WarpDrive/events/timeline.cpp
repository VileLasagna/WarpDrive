#include "WarpDrive/basesystem/factory.hpp"
#include "WarpDrive/events/timeline.hpp"
#include "WarpDrive/basesystem/displaymanager.hpp"


Timeline::Timeline()
{

	time = 0;
    nextKey = keys.begin();
	lastAdded = 0;

}

void Timeline::load(const std::string& )
{

	//load file here

}


void Timeline::update()
{

    time += DisplayManager::instance()->Dt();
    if(nextKey == keys.end())
	{
		return;
	}
    std::multiset<TimelineKey*,MyCompare>::iterator it = nextKey;
    while( it != keys.end() && time >= (*it)->Time())
	{
        (*it)->trigger();
		it++;
	}
    nextKey = it;

}

void Timeline::reset()
{
	time = 0;
    nextKey = keys.begin();
}

void Timeline::addKey(TimelineKey *key)
{
	if(key->Time() <= 0)
	{
		//If the key has a negative time value, interpret that as
		//positive time RELATIVE to the last added timeline key
		if(lastAdded)
		{
			float t = lastAdded->Time() + std::abs(key->Time());
			key->setTime(t);
		}
		else
		{
			key->setTime(0); //Defaults to 0;
		}
	}
	keys.insert(key);
	lastAdded = key;
    nextKey = keys.begin();
}

Timeline::~Timeline()
{
	for (std::multiset<TimelineKey*,MyCompare>::iterator it = keys.begin(); it != keys.end(); it++)
	{
		delete (*it);
	}
	keys.clear();
}
