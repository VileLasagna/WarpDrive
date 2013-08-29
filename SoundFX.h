#ifndef SOUND_FX_H
#define SOUND_FX_H

#include <string>
#include "SDL_mixer.h"
#include "SDL.h"

#include "SoundManager.h"
/*
 *	Objects of this class are used to play different sounds in the sound manager class.
 *	As this version, SoundManager uses SDL to manage sounds so that, although you can 
 *	load some types of music files with this class you're way better off loading them
 *	through the manager. The reason for this is because using it as a SoundFX would cause
 *	SDL to try and decompress the whole MP3 or whatsnot and sticking it into your memory,
 *	as opposed to properly buffering it. The Sound Manager DOES NOT manage the lifecycle
 *	of your SoundFX so when they're finished playing is up to you what to do with them.
 *	What it DOES manage is the real in-disk source of these objects, so you don't have to 
 *	worry about loading and closing files and whatnot.
 */

class SoundFX
{
public:

	SoundFX(SDL_RWops* source);
	~SoundFX();


	int getVolume() const {return volume;}
	void setVolume(int i) {volume = i;} //from 0 to 100. 50 is neutral, other values will adjust this when played by SoundManager
	
	int getLoop() const {return loop;}//how many times is this to be looped. -1 = forever
	void setLoop(int i) {loop = i;}

	unsigned int getFadeIn() const {return fadeIn;}//fadeIn and fadeOut are the time, in miliseconds, that this sound should fade
	void setFadeIn(int milis) {fadeIn = milis;}
	unsigned int getFadeOut() const {return fadeOut;}
	void setFadeOut(unsigned int milis) {fadeOut = milis;}
	void setFadeOutFrom(unsigned int pos) {fadeOutFrom = pos;} //this can't be set automatically. It's from when, in miliseconds, the sound should start fading out
	unsigned int getFadeOutFrom() const {return fadeOutFrom;}
	
	unsigned int getPlayed() const {return played;}//returns the estimate position on the file
	

	unsigned __int8 getDistance() const {return distance;}
	void setDistance (unsigned __int8 i) {distance = i;} //0 unregisters effect. 255 is the farthest possible (but still audible) 

	int getPosition() const {return position;} //this is an angle relative to what should be your "front"
	void setPosition(int deg) {position = deg;} //This is an angle! (0 = front, 90 = right)

	bool getReverseStereo() const {return reverseStereo;}
	void setReverseStereo(bool b) {reverseStereo = b;}

	int getChannel() const {return channel;}
	
	Mix_Chunk* getChunk(){return chunk;} 
	
	void setPanning(int i) {panning = i;} //0 unregisters effect. If distance+angle are set, this is ignored.
	int getPanning() const {return panning;} //0 is full-left. 128 = center. 255 is full-right

	void setType(const std::string& s) {type = s;} //Sound type for Manager's auto-volume
	const std::string& getType() const {return type;}

	void setPriority(bool b) {priority = b;} //Priority sounds aren't dropped unless extreme circunstances arise
	bool getPriority() {return priority;}

	void Halt() {halt = true;}
	bool getHalt() const {return halt;}


	bool hasFinished() const {return finished;}

	static bool hasFinished(const SoundFX& fx) {return fx.hasFinished();}

	
	

	


private:

	
	friend class SoundManager;

	void Finished(){finished = true;}
	void freeChunk(); //This is a safeguard against a possible coding mistake.
	void rewind() {played = 0; finished = false;}
	void addPlayed(int i) {played+=i;} //register that the sound has advanced i miliseconds (needed for planning fade-outs)
	void setChannel(int i) {channel = i;}//You better don't mess with this. It's used by SoundManager


	std::string type;
	int volume;
	int loop;
	int channel;
	int panning;
	unsigned int played; //ms already played in the file
	unsigned int fadeOut; //miliseconds to fade out.
	unsigned int fadeOutFrom; //time (in ms) from which the sound should start fading.
	unsigned int fadeIn;	//ms to fade in.
	unsigned __int8 distance;
	int position; //0 is directly in front. Angle increases clockwise (90 is right, 270 is left)
	bool reverseStereo;
	bool priority; //true means high proprity when cancelling channels to allocate more sounds;
	//bool recyclable;
	//unsigned __int32 lastplayed;
	Mix_Chunk* chunk;
	bool halt;
	bool finished;

};




#endif //SOUND_FX_H