#ifndef SPLASH_H
#define SPLASH_H

#include "GameState.h"
#include "Texture.h"
#include "Billboard.h"


class Splash:public GameState
{
public:

	Splash();
	int Update();
	void Draw();
	void Reset();

private:

	void onKeyboardEvent(const SDL_KeyboardEvent& e);
	void onJoyButtonEvent(const SDL_JoyButtonEvent&e);

	Texture* T;
	Billboard bg;
	float demotimer;

};

#endif //SPLASH_H