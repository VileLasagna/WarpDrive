#ifndef TIMELINE_KEY_PLAY_MUSIC_H
#define TIMELINE_KEY_PLAY_MUSIC_H

#include "BaseSystem/Game.h"
#include "Events/TimelineKey.h"
#include "Sound/SoundManager.h"

#include <string>


class TKPlayMusic: public TimelineKey
{
public:

	TKPlayMusic(float Time = 0, const std::string& Filename = "", int FadeIn = 0)
	{
		time = Time;
		filename = Filename; 
		if(filename != ""){SoundManager::instance()->loadMusic(filename.c_str());} 
		fadein = FadeIn;
	}
	void Trigger()
	{
		if(filename != "")
		{
			SoundManager::instance()->FadeInMusic(fadein);
		}
	}

protected:

	std::string filename;
	int fadein;

};

#endif //TIMELINE_KEY_PLAY_MUSIC_H
