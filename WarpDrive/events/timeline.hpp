#ifndef WD_TIMELINE_HPP_DEFINED
#define WD_TIMELINE_HPP_DEFINED

#include <set>
#include <string>

#include "events/timelinekey.hpp"

class Timeline
{

public:
	
	Timeline();
	
    void load(const std::string& file);
	void addKey(TimelineKey* key);
    void update();
    void reset();
    bool Finished()const {return (nextKey == keys.end());}

	~Timeline();

private:

	struct MyCompare
	{
		bool operator()(TimelineKey* p1, TimelineKey* p2)
		{
            return p1->Time()< p2->Time();
		}
	};
	std::multiset<TimelineKey*, MyCompare> keys;

    int64_t time;

    std::multiset<TimelineKey*,MyCompare>::iterator nextKey;
	TimelineKey* lastAdded;
};

#endif //WD_TIMELINE_HPP_DEFINED
