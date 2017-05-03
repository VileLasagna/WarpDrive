#ifndef WD_SOUND_MANAGER_HPP_DEFINED
#define WD_SOUND_MANAGER_HPP_DEFINED


#include <string>
#include <map>
#include <vector>
#include <set>
#include <cstdio>

class SoundFX;
struct SDL_RWops;
using Mix_Music = struct _Mix_Music;

class SoundManager
{
enum class Quality{ NO_SOUND = 0,SOUND_LOW_FI = 1, SOUND_MID_FI = 2, SOUND_HI_FI = 3};

private:	//this class is a singleton
	SoundManager();

public:

    constexpr static unsigned int ChannelOoB = 256;

	~SoundManager();

	static SoundManager* instance();
	SDL_RWops* loadSound(const std::string& filename);
	void playSound(SoundFX* FX);
	//int getMemoryUsage() const{return mem;}; //returns how much memory is being used by the RWops sourcefiles. TODO-> Implementation
	void setTypeVolume(std::string type, int volume); //volumes from 0 to 100
    int TypeVolume(std::string type); //returns -1 if the type is not yet registered in the manager.
	void setAutoChannels(bool b) {autochannels = b;} //if true, more channels will be allocated automatically, should the need arise.
	void update(); //needed to pre-set fadeOuts
	static void clear();

	int loadMusic(const std::string& filename); //0 == error, 1 == OK, 2 == Music on Hold (for fadeOut to end);
	void setMusicLoop(int i) {musLoops = i;} //number of times to loop the music. -1 = forever, 0 plays once
    int MusicLooping() const {return musLoops;}
    void setMusicVolume(unsigned int i); //volume from 0 to 100%
    int MusicVolume() const {return musVolume/128;}
    bool pauseMusic(bool b = false); //returns the current state and, if the argument is true, pauses the playback (and returns true. duh!)
    void resumeMusic();
	bool PlayMusic(); //false = Error
    bool fadeInMusic(int ms); //Same as PlayMusic, but the Music fades in through ms miliseconds
    bool setMusicPosition(unsigned int ms); //sets the music position to (you'll never guess) ms miliseconds from the start! returns true if OK
    bool advanceMusic(unsigned int ms); //Advances the music ms milis from where it should be right now. a return of false means and error
    bool haltMusic(int ms = 0); //Halts the music, fading out for ms miliseconds;
    int MusicPlaying(); //0 = not, 1 = yes, 2 = yes, but it's paused
	
	static int soundQuality(int i = -1);	/* sets the Sound Quality. Use NO_SOUND,SOUND_LOW_FI,SOUND_MID_FI,SOUND_HI_FI
											 * Should you turn it off, this is the method to restart things again
											 * returns the current SoundQuality setting. Pass -1 to just check the current quality level;
											 */
	bool loadSoundSet(std::set<std::string> newset);
	bool SystemActive(); //Returns false if the system is dormant(setSoundQuality(NO_SOUND);)	
	
	SoundManager operator = (const SoundManager& ) = delete;
	SoundManager(const SoundManager& ) = delete;

protected:

	//These are not private because one may want to use an external program to managed part or whole of of the sound system
	//And derive the class to do that. SDL_Mixer DOES give support to that, to some extent

	static SoundManager* instance(bool reset);
	static bool destructing(bool toggle = false);

	bool applyQuality();
	static bool hasInst(bool b = false);
    unsigned int FirstFreeChannel();
    static void cleanChannel(int i); //to be hooked up and called automatically by Mix_ChannelFinished
	//static void cleanMusic();
	int mem;
	std::map<std::string,int> soundTypes; //the pairedvalue is the volume at which that kind of sound will be played.
	std::map<std::string,FILE*> sourcefiles;
	bool autochannels;
	std::vector<SoundFX*> channels; //A pointer to an effect currently being played at [channel] or NULL if the channel is free
	Mix_Music* music;
	int musLoops;
    uint8_t musVolume;
	unsigned int musPos;
    std::string musicOnQueue;
    std::string currentMusic;
	int audio_rate;
	FILE* FILECOPY(FILE* F);
};

#endif //WD_SOUND_MANAGER_HPP_DEFINED
