
#ifndef TIMELINE_H
#define TIMELINE_H


#include <set>
#include <string>
#include "Events/TimelineKey.hpp"

class Timeline
{
public:
	
	Timeline();
	
	void Load(const std::string& file);
	void addKey(TimelineKey* key);
	void Update();
	void Reset();
	bool isFinished()const {return (NextKey == keys.end());}

	~Timeline();

private:

	struct MyCompare
	{
		bool operator()(TimelineKey* p1, TimelineKey* p2)
		{
			return p1->getTime()< p2->getTime();
		}
	};
	std::multiset<TimelineKey*, MyCompare> keys;

	float time;

	std::multiset<TimelineKey*,MyCompare>::iterator NextKey;
	TimelineKey* lastAdded;
};

#endif //TIMELINE_H
