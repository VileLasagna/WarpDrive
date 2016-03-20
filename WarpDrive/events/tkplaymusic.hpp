#ifndef WD_TIMELINE_KEY_PLAY_MUSIC_HPP_DEFINED
#define WD_TIMELINE_KEY_PLAY_MUSIC_HPP_DEFINED

#include <string>

#include "basesystem/game.hpp"
#include "events/timelinekey.hpp"
#include "sound/soundmanager.hpp"

class TKPlayMusic: public TimelineKey
{

public:

	TKPlayMusic(float Time = 0, const std::string& Filename = "", int FadeIn = 0)
	{
		time = Time;
		filename = Filename; 
        if(filename != "") {SoundManager::instance()->loadMusic(filename.c_str());}
		fadein = FadeIn;
	}
	void trigger()
	{
		if(filename != "")
		{
            SoundManager::instance()->fadeInMusic(fadein);
		}
	}

protected:

	std::string filename;
	int fadein;

};

#endif //WD_TIMELINE_KEY_PLAY_MUSIC_HPP_DEFINED
