#include "GOScreen.h"
#include "BaseSystem/Game.h"

GOScreen::GOScreen()
{

	T = new Texture();
	T->LoadTexture("data/GOScreen.png"); 
	bg = Billboard(82,Vec3f(10,15,0));
	self = 2;
	ret = self;

};

int GOScreen::Update()
{
    SDLEventHandler::Update();
	return ret;
}

void GOScreen::Draw()
{
	T->UseThisTexture();
	bg.Draw();
	T->UseNoTexture();
}

void GOScreen::onJoyButtonEvent(const SDL_JoyButtonEvent& e)
{
	if (e.type == SDL_JOYBUTTONDOWN)
	{
		if(e.button == 3)
		{
			ret = -1;
		}
		else
		{
			Game::instance()->resetState(1);
			ret = 1;
		}
	}
}

void GOScreen::onKeyboardEvent(const SDL_KeyboardEvent &e)
{
	if (e.keysym.sym == SDLK_ESCAPE)
	{
		ret = -1;
	}
	else
	{
		if(e.type == SDL_KEYDOWN)
		{
			Game::instance()->resetState(1);
			ret = 1;
		}
	}
}


