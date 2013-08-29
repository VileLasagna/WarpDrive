#include "SoundFX.h"
#include "Err.h"


SoundFX::SoundFX(SDL_RWops* source)
{
	chunk = Mix_LoadWAV_RW(source, 1);
	volume = 128;
	loop = 0;
	channel = -1;
	panning = 128;
	played = 0;
	fadeOut = 0;
	fadeOutFrom = -1;
	fadeIn = 0;
	distance = 0;
	position = 0;
	reverseStereo = false;
	priority = false;
	halt = false;
	finished = false;
	type = "Sound";
}

SoundFX::~SoundFX()
{
	//some safeguarding in case someone managed to shut down the SoundManager before this was removed
	if(chunk)
	{
		Mix_FreeChunk(chunk);
	}
}

void SoundFX::freeChunk()
{
	if(chunk)
	{
		Mix_FreeChunk(chunk);
		chunk = 0;
	}
}