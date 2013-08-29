#include "Splash.h"
#include "Game.h"
#include "Camera.h"

Splash::Splash()
{

	T = new Texture();
	T->LoadTexture("data/Splash.png"); 
	bg = Billboard(82,Vec3f(10,15,0));
	self = 0;
	ret = self;
	Camera* Cam1 = new Camera();
	Cam1->setName("Cam1");
	Game::instance()->addObject(Cam1);
	Cam1->setPos(Vec3f(10,10,40));
	Cam1->setTarget(Vec3f(10,15,0));
	Cam1->Use();
	Reset();

};

int Splash::Update()
{
	EventHandler::Update();
	demotimer -= DisplayManager::instance()->getDtSecs();
	Game::iterator it = Game::iterator("Camera");
	if (!it.seekName("Cam1"))
	{
		assert(0);
	}
	GameObject* GO = it;
	((Camera*)GO)->Use();
	if (demotimer <= 0)
	{
		Game::instance()->resetState(3);
		ret = 3;
	}
	return ret;
}

void Splash::Draw()
{
	T->UseThisTexture();
	bg.Draw();
	T->UseNoTexture();

}

void Splash::onJoyButtonEvent(const SDL_JoyButtonEvent& e)
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

void Splash::onKeyboardEvent(const SDL_KeyboardEvent &e)
{
	if (e.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYDOWN)
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

void Splash::Reset()
{
	demotimer = 7; 
	ret = self;
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


	
	glViewport(0,0,DisplayManager::instance()->getSize().first,DisplayManager::instance()->getSize().second);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)(DisplayManager::instance()->getSize().first)/(float)(DisplayManager::instance()->getSize().second), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	

	GLfloat light_direction[] = {0, 10, 15, 1};
	GLfloat ambientL[] = {1,1,1,1};
	GLfloat diffuseL[] = {1,1,1,1};
	GLfloat specularL[] = {1,1,1,1};


	glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientL);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseL);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularL);

    glClearColor(0, 0 ,0, 1);
	Game::iterator it = Game::iterator("Camera");
	if (!it.seekName("Cam1"))
	{
		assert(0);
	}
	GameObject* GO = it;
	((Camera*)GO)->setPos(Vec3f(10,10,40));
	((Camera*)GO)->setTarget(Vec3f(10,15,0));
	((Camera*)GO)->Use();
}

