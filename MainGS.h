#ifndef MAIN_GAME_STATE_H
#define MAIN_GAME_STATE_H

#include "GameState.h"
#include "Camera.h"
#include "Billboard.h"
#include "Texture.h"


class MainGS: public GameState
{
public:

	MainGS();
	int Update();
	void Draw();
	void Reset();
	void Pause();

private:

	void onKeyboardEvent(const SDL_KeyboardEvent &e);
	void onJoyButtonEvent(const SDL_JoyButtonEvent&e);
	void onJoyAxisEvent(const SDL_JoyAxisEvent &e);
	void onActiveEvent(const SDL_ActiveEvent& e);
	Texture* bg;
	Billboard horizon;
	bool isPaused;


};



#endif //MAIN_GAME_STATE_H