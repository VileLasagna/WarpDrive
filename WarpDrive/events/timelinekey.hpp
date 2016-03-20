#ifndef WD_TIMELINE_KEY_HPP_DEFINED
#define WD_TIMELINE_KEY_HPP_DEFINED

class TimelineKey
{

public:

	TimelineKey(){}
	TimelineKey(float T)
	{
		time = T;
	}
    virtual void trigger() = 0;

    float Time() const
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

#endif //WD_TIMELINE_KEY_HPP_DEFINED
