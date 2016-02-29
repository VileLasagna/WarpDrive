#ifndef GOScreen_H
#define GOScreen_H

#include "basesystem/GameState.h"
#include "Display/Texture.h"
#include "3DMaths/Billboard.h"


class GOScreen:public GameState
{
public:

	GOScreen();
	int Update();
	void Draw();
	void Reset(){ret = 2;}

private:

	void onKeyboardEvent(const SDL_KeyboardEvent& e);
	void onJoyButtonEvent(const SDL_JoyButtonEvent&e);

	Texture* T;
	Billboard bg;

};

#endif //GOScreen_H
