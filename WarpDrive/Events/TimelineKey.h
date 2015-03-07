
#ifndef TIMELINE_KEY_H
#define TIMELINE_KEY_H


class TimelineKey
{

public:
	TimelineKey(){}
	TimelineKey(float T)
	{
		time = T;
	}
	virtual void Trigger() = 0;


	float getTime() const
	{
		return time;
	}
	
	void setTime(float t)
	{
		time = t;
	}
	virtual ~TimelineKey() = default;

protected:

	float time;
};

#endif //TIMELINE_KEY_H
