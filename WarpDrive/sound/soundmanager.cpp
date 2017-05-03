#include "WarpDrive/sound/soundmanager.hpp"

#include <time.h>
#include <math.h>

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>

#include "WarpDrive/sound/soundfx.hpp"
#include "WarpDrive/basesystem/err.hpp"
#include "WarpDrive/basesystem/game.hpp"


SoundManager::SoundManager()
{
	SoundManager::destructing(SoundManager::destructing());
	SDL_Init(SDL_INIT_AUDIO);
	SoundManager::hasInst(!SoundManager::hasInst()); //the internal call SHOULD return false unless things are being MADE to crash but...
	if(SoundManager::soundQuality())
	{
        audio_rate = 11025*(static_cast<int>(pow(2.f,SoundManager::soundQuality()-1)));
	}
	else
	{
		audio_rate = 0;
	}
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
 
	if(audio_rate)
	{
		if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) 
		{
			Err::Report(std::string("Unable to initialize audio: ") + Mix_GetError());
		}
		Mix_ChannelFinished(&SoundManager::cleanChannel);
		for(int i = 0; i < Mix_AllocateChannels(-1); i++)
		{
			channels.push_back(0);
			Mix_Volume(i,MIX_MAX_VOLUME/2);
		}
	}
	musPos = 0;
	musLoops = -1;
	music = 0;
    musicOnQueue = "";
    currentMusic = "";
}

SoundManager::~SoundManager()
{
	SoundManager::destructing(!SoundManager::destructing());
	Mix_HaltChannel(-1);
	Mix_HaltMusic();
	for (std::vector<SoundFX*>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (*it)
		{	//If the chunk isn't freed now, we may have some real nasty stuff happening
			(*it)->freeChunk();
		}
		//BUT we don't want the destructor trying to delete these objects since they are managed by their parents
		//rather than the manager.
		(*it) = 0;
	}
	for(std::map<std::string,FILE*>::iterator it = sourcefiles.begin(); it != sourcefiles.end(); it++)
	{
		if (it->second)
		{
			fclose(it->second);
		}
	}
	if (music)
	{
		Mix_FreeMusic(music);
	}

	Mix_CloseAudio();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
	SoundManager::hasInst(SoundManager::hasInst());//set this to false jsut in case this manages to get instantiated again
}

SoundManager* SoundManager::instance(bool reset)
{

	static SoundManager* inst = new SoundManager();
	if (reset)
	{
		inst = 0;
	}
	else
	{
		if (inst == 0) //the manager has been destroyed ans is being recreated.
		{
			inst = new SoundManager();
		}
	}
	return inst;
}

SoundManager* SoundManager::instance()
{
	return SoundManager::instance(false);
}

void SoundManager::clear()
{
	delete SoundManager::instance();
	SoundManager::instance(true);
}


SDL_RWops* SoundManager::loadSound(const std::string &filename)
{
	if(!SoundManager::soundQuality()){return 0;}
	//if(sourcefiles.find(filename) != sourcefiles.end())
	//{
	//	return SDL_RWFromFP(FILECOPY(sourcefiles[filename]),0); //File already loaded
	//}
	//else
	//{
	//	sourcefiles[filename] = fopen(filename.c_str(), "rb");
	//	if(!sourcefiles[filename])
	//	{
	//		Err::Report("Couldn't load sound file: "+filename);
	//		return 0;
	//	}
	//	else
	//	{
	//		//TODO: Automatic memory management
	//		return SDL_RWFromFP(FILECOPY(sourcefiles[filename]),0);
	//	}
	//}
	SDL_RWops* ret = SDL_RWFromFile(filename.c_str(), "rb");
	if (!ret)
	{
		Err::Report("UNable to load Sound File:" + filename);
	}
	return ret;
}

int SoundManager::TypeVolume(std::string type)
{
	if(!SoundManager::soundQuality()){return 0;}
	std::map<std::string,int>::iterator it = soundTypes.find(type);
	if (it == soundTypes.end())
	{
		return -1;
	}
	else
	{
		return (*it).second;
	}
}

unsigned int SoundManager::FirstFreeChannel()
{
    if(!SoundManager::soundQuality()){return ChannelOoB;}
	for (unsigned int i = 0; i < channels.size(); i++)
	{
		if (!channels[i])
		{
			return i;
		}
	}
    return ChannelOoB;
}

void SoundManager::setTypeVolume(std::string type, int volume)
{
	soundTypes[type] = volume;
}

void SoundManager::playSound(SoundFX *FX)
{
	if(!SoundManager::soundQuality()){return;}
    unsigned int c = FirstFreeChannel();
    if (c == ChannelOoB)
	{
		if (autochannels)
		{
            c = static_cast<unsigned int>(channels.size());
			auto j = channels.size();
            auto i = Mix_AllocateChannels(static_cast<int>(channels.size()/2));
            channels.resize(channels.size()+static_cast<unsigned int>(i));
			while(j != channels.size())
			{
                Mix_Volume(static_cast<int>(j++),MIX_MAX_VOLUME/2);
			}
		}
		else //stop the oldest non-priority sound being played
		{
            std::pair<unsigned int,unsigned int> drop;
			drop.first = 0;
			drop.second = 0;
			for(unsigned int i = 0; i<channels.size(); i++)
			{
                if ( (channels[i]->Played() > drop.second) && (!channels[i]->getPriority()) ) //we already know all channels are busy
				{
					drop.first = i;
                    drop.second = channels[i]->Played();
				}
			}
			if (drop.second == 0) //bastard set no-auto and made all sounds priority. DOH!
			{	
                //YES! We drop a channel at random. Why not?
				Err::Notify("All SoundManager channels busy playing priority Sounds!");			
                drop.first = ( static_cast<unsigned int>(Game::instance()->RNGrange( static_cast<unsigned int>(channels.size())) ) );
			}
            Mix_HaltChannel(static_cast<int>(drop.first));
			c = drop.first;
		}
	}

	if ( FX->FadeIn() > 0) //Yeah, I know I could just use a fadeIn of 0 seconds but god knows how is that implemented internally
	{
		Mix_FadeInChannel(c,FX->getChunk(),FX->Loop(),FX->FadeIn());
	}
	else
	{
		Mix_PlayChannel(c,FX->getChunk(),FX->Loop());
	}
    int v = TypeVolume(FX->Type());
	if ( v == -1)
	{
		v = MIX_MAX_VOLUME;
		setTypeVolume(FX->Type(),v);
	}
    Mix_Volume(static_cast<int>(c), (v * ((FX->Volume()*2)/100) ) );
	if (FX->Position())
	{
        Mix_SetPosition(static_cast<int>(c), static_cast<Sint16>(FX->Position()), static_cast<Uint8>(FX->Distance()));
	}
	else
	{
		if(FX->Distance())
		{
            Mix_SetDistance( static_cast<int>(c), static_cast<Uint8>(FX->Distance()) );
		}
        Mix_SetPanning(static_cast<int>(c), static_cast<Uint8>(255-(FX->Panning())), static_cast<Uint8>(FX->Panning()) );
	}
	channels[c] = FX;
	FX->setChannel(c);
}

void SoundManager::cleanChannel(int i)
{
	if(!SoundManager::destructing()) //the destructor has s'more stuff to do
	{
        SoundManager::instance()->channels[static_cast<unsigned int>(i)]->Finished();
        SoundManager::instance()->channels[static_cast<unsigned int>(i)] = 0;//This doesn't call HALT because channels stop on their own when the file ends
	}
}

bool SoundManager::destructing(bool toggle)
{
	static bool dest = false;
	if (toggle)
	{
		dest = !dest;
	}
	return dest;
}

void SoundManager::update()
{
	static unsigned int oldms = SDL_GetTicks();
    unsigned int ms = SDL_GetTicks();
    unsigned int dt = ms - oldms;
    oldms = ms;
	if(!SoundManager::soundQuality()){return;}
    if(!pauseMusic())
	{
		musPos+=dt;
	}
	for (unsigned int i = 0; i < channels.size(); i++)
	{
		if (channels[i])
		{
			channels[i]->addPlayed(dt);
            if(channels[i]->FadeOut() && (channels[i]->Played() >= channels[i]->FadeOutFrom()) )
			{
                Mix_FadeOutChannel( static_cast<int>(i), static_cast<int>(channels[i]->FadeOut()) );
			}
            if(channels[i]->Halted())
			{
                Mix_HaltChannel(static_cast<int>(i));
			}
		}
	}
    if (musicOnQueue.compare("")) // If Music on Queue is not an empty string
	{
        loadMusic(musicOnQueue);
	}
}

void SoundManager::setMusicVolume(unsigned int i)
{
	if(!SoundManager::soundQuality()){return;}
    musVolume = static_cast<Uint8>(i*1.28);
	Mix_VolumeMusic(musVolume);
}

bool SoundManager::pauseMusic(bool b)
{
	if(!SoundManager::soundQuality()){return 0;}
	if(b)
	{
		if(Mix_PausedMusic())
		{
			Mix_ResumeMusic();
		}
		else
		{
			Mix_PauseMusic();
		}
	}
	return Mix_PausedMusic();
}


void SoundManager::resumeMusic()
{
	if(!SoundManager::soundQuality()){return;}
	Mix_ResumeMusic();
}

bool SoundManager::fadeInMusic(int ms)
{
	if(!SoundManager::soundQuality()){return 0;}
	if(!music)
	{
		return false;
	}
	if(ms)
	{
		return !Mix_FadeInMusic(music,musLoops,ms);
	}
	else
	{
		return !Mix_PlayMusic(music,musLoops);
	}
}

bool SoundManager::PlayMusic()
{
	if(!SoundManager::soundQuality()){return 0;}
    return fadeInMusic(0);
}

bool SoundManager::setMusicPosition(unsigned int ms)
{
	if(!SoundManager::soundQuality()){return 0;}
	if(!music){return 0;}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
	switch(Mix_GetMusicType(music))
	{
	case MUS_MP3:
		{
			Mix_RewindMusic();
			Mix_SetMusicPosition(ms/1000);
			musPos = ms;
			return true;
		}
	case MUS_OGG:
		{
			Mix_SetMusicPosition(ms/1000);
			musPos = ms;
			return true;;
		}
	case MUS_MOD:
		{
			//It IS supported by SDL_Mixer but I need some knowledge about the format to implement this
        }[[clang::fallthrough]];
    default:
		{
			Err::Notify("Cannot change position of current music format!");
		}
	}
#pragma clang diagnostic pop
	return false;
}

int SoundManager::loadMusic(const std::string& filename)
{
	if(!SoundManager::soundQuality()){return 0;}
    if (!filename.compare(currentMusic))
	{
		return 1; //The file is already loaded. Lovely!
	}
	if (Mix_PlayingMusic() )
	{
		if(Mix_FadingMusic() == MIX_FADING_OUT)
		{
            musicOnQueue = filename;
			return 2;
		}
		else
		{
            haltMusic();
		}
	}
    currentMusic = "";
    musicOnQueue = "";
	if (music)
	{
		Mix_FreeMusic(music);
	}
	music = 0;
	music = Mix_LoadMUS(filename.c_str());
	if (music)
	{
        currentMusic = filename;
		return 1;
	}
	else
	{
		Err::Notify("Couldn't load music file: " +filename);
		return 0;
	}
}

bool SoundManager::haltMusic(int ms)
{
	if(!SoundManager::soundQuality()){return 0;}
	if(!ms)
	{
		Mix_HaltMusic();
        if(!MusicPlaying())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return Mix_FadeOutMusic(ms);
	}
}

int SoundManager::MusicPlaying()
{
	if(!SoundManager::soundQuality()){return 0;}
	if(Mix_PlayingMusic())
	{
		if(Mix_PausedMusic())
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return 0;
	}
}

bool SoundManager::advanceMusic(unsigned int ms)
{
	if(!SoundManager::soundQuality()){return 0;}
	return setMusicPosition(musPos+ms);
}

//bool SoundManager::loadSoundSet(std::set<std::string> newset)
//{
//	//TODO The removing part should crash
//	if(!SoundManager::soundQuality()){return 0;}
//	bool ret = true;
//	for(std::map<std::string,FILE*>::iterator it = sourcefiles.begin(); it != sourcefiles.end(); it++)
//	{
//		std::set<std::string>::iterator nit = newset.find(it->first);
//		if(nit != newset.end())
//		{
//			newset.erase(nit);
//		}
//		else
//		{
//			sourcefiles.erase(it);
//		}
//	}
//	for(std::set<std::string>::iterator nit = newset.begin(); nit != newset.end(); nit++)
//	{
//		if( !loadSound(*nit) )
//		{
//			ret = false;
//		}
//	}
//	return ret;
//}

bool SoundManager::hasInst(bool b)
{
	static bool hasIt = false;
	if (b) {hasIt = !hasIt;}
	return hasIt;
}

int SoundManager::soundQuality(int i)
{
	static int currentQuality = 2;
	if (i != -1)
	{
		if (i > 3)
		{
			currentQuality = 3;
		}
		else
		{
			currentQuality = i;
		}
	}
	else
	{
		return currentQuality;
	}
	if(SoundManager::hasInst())
	{
		if(!SoundManager::instance()->applyQuality())
		{
			if (currentQuality !=0)
			{
				currentQuality = 0;
				SoundManager::instance()->applyQuality(); //shut it down for good measure.
			}
			currentQuality = 0; //The thing has crashed while rebooting.
		}
	}
	return currentQuality;
}

bool SoundManager::applyQuality()
{
	if (!SoundManager::soundQuality())
	{
		//Stop all sound
		Mix_HaltChannel(-1);
		Mix_HaltMusic();
		//Free all memory
		Mix_FreeMusic(music);
		for (std::map<std::string,FILE*>::iterator it; it != sourcefiles.end(); it++)
		{
			delete(it->second);
			sourcefiles.erase(it);
		}
		//stop the system
		Mix_CloseAudio();
		audio_rate = 0;
		return true;
	}
	else
	{
		int i = SoundManager::soundQuality();
		i-=1;
		//LO_FI will generate 11Khz,MID 22 and HI 44;
        int new_rate = 11025*(static_cast<int>(pow(2.,i)) );
		if( new_rate == audio_rate)
		{
			return true;
		}
		else
		{
			Mix_HaltChannel(-1);
			Mix_HaltMusic();
			audio_rate = 0;
            for(unsigned int j = 0; j < channels.size(); j++)
			{
                cleanChannel(static_cast<int>(j));
			}
            int mus = MusicPlaying();
            bool muspause = pauseMusic();
			Mix_CloseAudio();
			Uint16 audio_format = AUDIO_S16SYS;
			int audio_channels = 2;
			int audio_buffers = 4096;
			if(Mix_OpenAudio(new_rate,audio_format,audio_channels,audio_buffers))
			{
				audio_rate = new_rate;
				channels.resize(0);
                for(int j = 0; j < Mix_AllocateChannels(-1); j++)
				{
					channels.push_back(0);
                    Mix_Volume(j,MIX_MAX_VOLUME/2);
				}
				if(mus)
				{
					PlayMusic();
					setMusicPosition(musPos);
					if(muspause)
					{
                        pauseMusic(true);
					}
				}
				return true;
			}
			return false;
		}
	}	
}

FILE* SoundManager::FILECOPY(FILE *F)
{
	FILE* ret = new FILE(*F);
	return ret;
}
