#include "MainGS.h"
#include "basesystem/Game.h"
#include "Display/Camera.h"
#include "Brick.h"
#include "Grid.h"
#include "basesystem/Score.h"
#include "Sound/SoundManager.h"
#include <time.h>
#include <math.h>
#include <GL/glu.h>


MainGS::MainGS()
{

    self = 1;
    ret = self;
    //Game::instance()->addObject(new Brick);
    Game::instance()->addObject(new Grid);

    //Game::instance()->addObject(new Score);
    bg = new Texture();
    bg->LoadTexture("data/Background.png");
    horizon = Billboard(200,Vec3f(10,20,-50));
    isPaused = false;
    Reset();

}

int MainGS::Update()
{
    SDLEventHandler::Update();

    Game::instance()->UpdateObjects();
    Game::iterator it = Game::iterator("PlayGrid");
    GameObject* p = it;
    if( ((Grid*) p)->GameOver())
    {
        Game::instance()->resetState(2);
        ret = 2;
    }

    return ret;
}

void MainGS::onKeyboardEvent(const SDL_KeyboardEvent& e)
{
    if(isPaused && (e.keysym.sym != SDLK_RETURN && e.keysym.sym != SDLK_ESCAPE))
    {
        return;
    }
    GameState::onKeyboardEvent(e);
    if(e.keysym.sym == SDLK_UP && e.type == SDL_KEYDOWN)
    {
        Game::iterator it = Game::iterator("PlayGrid");
        GameObject* p = it;
        ((Grid*) p)->spin();
    }
    if(e.keysym.sym == SDLK_LEFT && e.type == SDL_KEYDOWN)
    {
        Game::iterator it = Game::iterator("PlayGrid");
        GameObject* p = it;
        ((Grid*) p)->nudge(true);
    }
    if(e.keysym.sym == SDLK_RIGHT && e.type == SDL_KEYDOWN)
    {
        Game::iterator it = Game::iterator("PlayGrid");
        GameObject* p = it;
        ((Grid*) p)->nudge(false);
    }
    if(( e.keysym.sym == SDLK_SPACE || e.keysym.sym == SDLK_DOWN)  && e.type == SDL_KEYDOWN)
    {
        Game::iterator it = Game::iterator("PlayGrid");
        GameObject* p = it;
        ((Grid*) p)->drop();
    }
    if(e.keysym.sym == SDLK_RETURN && e.type == SDL_KEYDOWN)
    {
        Pause();
    }

}

void MainGS::onJoyAxisEvent(const SDL_JoyAxisEvent& e)
{
    if(isPaused)
    {
        return;
    }
    int halfrange = 32768/2;
    if(e.value < halfrange && e.value > (-halfrange))
    {
        return;
    }
    if(e.axis == 0)
    {
        if (e.value < 0)
        {
            Game::iterator it = Game::iterator("PlayGrid");
            GameObject* p = it;
            ((Grid*) p)->nudge(true);
        }
        else
        {
            Game::iterator it = Game::iterator("PlayGrid");
            GameObject* p = it;
            ((Grid*) p)->nudge(false);
        }
    }
    if (e.axis == 1)
    {
        if(e.value > 0)
        {
            Game::iterator it = Game::iterator("PlayGrid");
            GameObject* p = it;
            ((Grid*) p)->drop();
        }
        else
        {
            Game::iterator it = Game::iterator("PlayGrid");
            GameObject* p = it;
            ((Grid*) p)->spin();
        }
    }
}

void MainGS::onJoyButtonEvent(const SDL_JoyButtonEvent &e)
{
    if(e.type == SDL_JOYBUTTONDOWN)
    {
        if(e.button == 2)
        {
            Pause();
        }
        if (e.button == 3)
        {
            ret = -1;
        }
        if(isPaused)
        {
            return;
        }
        else
        {
            if(e.button == 1)
            {
                Game::iterator it = Game::iterator("PlayGrid");
                GameObject* p = it;
                ((Grid*) p)->spin();
            }
            if(e.button == 0)
            {
                Game::iterator it = Game::iterator("PlayGrid");
                GameObject* p = it;
                ((Grid*) p)->drop();
            }
        }
    }

}

#pragma warning("TODO - URGENT")
/**void MainGS::onActiveEvent(const SDL_ActiveEvent& e)
{
    if (e.gain == 0 && (!isPaused))
    {
        Pause();
    }
}
*/

void MainGS::Pause()
{
    isPaused = !isPaused;
    Game::iterator it = Game::iterator("PlayGrid");
    if(isPaused)
    {
        Game::instance()->removeActiveObject(it);
    }
    else
    {
        Game::instance()->addActiveObject(it);
    }
}

void MainGS::Draw()
{
    Game::iterator it = Game::iterator("Camera");
    if (!it.seekName("Cam1"))
    {
        assert(0);
    }
    GameObject* GO = it;
    ((Camera*)GO)->Use();
    bg->UseThisTexture();
    horizon.Draw();
    bg->UseNoTexture();
    Game::instance()->DrawObjects();

}

void MainGS::Reset()
{
    srand(time(0));
    self = 1;
    ret = self;

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);


    GLfloat light_direction[] = {0, 10, 15, 1};
    GLfloat ambientL[] = {1,1,1,1};
    GLfloat diffuseL[] = {1,1,1,1};
    GLfloat specularL[] = {1,1,1,1};


    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientL);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseL);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularL);
    glViewport(0,0,DisplayManager::instance()->getSize().first,DisplayManager::instance()->getSize().second);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)(DisplayManager::instance()->getSize().first)/(float)(DisplayManager::instance()->getSize().second), 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0, 0 ,0, 1);

    std::set<std::string> obset;
    obset.insert("brick");
    obset.insert("PlayGrid");
    obset.insert("score");
    Game::instance()->addActiveTypes(obset);
    Game::instance()->addDrawnTypes(obset);

    Game::iterator it = Game::iterator("PlayGrid");
    GameObject* p = it;
    ((Grid*) p)->Reset();
    //it = Game::iterator("score");
    //p = it;
    //((Score*) p)->Reset();
    SoundManager::instance()->loadMusic("data/Elevation.mp3");
    SoundManager::instance()->setMusicLoop(-1);
    SoundManager::instance()->PlayMusic();

}
