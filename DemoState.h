#ifndef DEMO_STATE_H
#define DEMO_STATE_H

#include "GameState.h"
#include "Timeline.h"
#include "Texture.h"


class DemoState: public GameState
{
public:

	DemoState();
	void Draw();
	int Update();
	void Reset();

private:

	Timeline* demo;
	float timer;
	Texture* Splash;


	void onKeyboardEvent(const SDL_KeyboardEvent& e);
	void onJoyButtonEvent(const SDL_JoyButtonEvent& e);

};



#endif //DEMO_STATE_H