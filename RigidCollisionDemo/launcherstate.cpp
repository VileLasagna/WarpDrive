#include "launcherstate.hpp"
#ifdef WIN32
    #include <Windows.h>
#endif //WIN32
#include "GL/glu.h"
#include <string>

#include "WarpDrive/basemaths/sphere.hpp"
#include "WarpDrive/basesystem/game.hpp"
#include "WarpDrive/physics/rbpcollision.hpp"

LauncherState::LauncherState()
   :floor(Vec3f(0,1,0),0)
{
    self = 0;
    ret = self;
    reset();

    cam.setTarget(Vec3f(0,0,0));
    cam.setPos(Vec3f(0,400,-700));
    cam.use();
    floor.drawAsWireframe(true);
    floor.setDrawn(100,100,60);
    floor.drawNormal(true);

    float minX = -3000;
    float minZ = -3000;
    float X = 6000;
    float Z = 6000;
    Game::instance()->quickSeedRNG();
    size_t numRows = 20;
    for(size_t row = 0; row < numRows; row++)
    {
        for(size_t column = 0; column < numRows; column++)
        {
            Ball* b0 = new Ball();
            b0->setRadius(10+(Game::instance()->RNGrange(50)));
            b0->setPos(Vec3f(minX+( (X/numRows)*row),1500+static_cast<float>(( (Game::instance()->RNGrange(200)-100) *10)),minZ+( (Z/numRows)*column)));
            b0->setVel(Vec3f(0,0,0));
            Game::instance()->addObject(b0);
        }
    }

    Game::instance()->addDrawnType("Ball");
    Game::instance()->addActiveType("Ball");
//    brute.load("Ball", "Ball", &LauncherState::ballsTouchedSoGay);
//    rdc.load("Ball", "Ball", &LauncherState::ballsTouchedSoGay);
//    brute.load("Ball", "Ball", [](GameObject* a, GameObject* b){ dynamic_cast<Ball*>(a)->setColour(GLRGBColour(0.8f,0.2f,0.7f));
//                                                                 dynamic_cast<Ball*>(b)->setColour(GLRGBColour(0.8f,0.2f,0.7f));});
//    rdc.load("Ball", "Ball", [](GameObject* a, GameObject* b){ dynamic_cast<Ball*>(a)->setColour(GLRGBColour(0.8f,0.2f,0.7f));
//                                                               dynamic_cast<Ball*>(b)->setColour(GLRGBColour(0.8f,0.2f,0.7f));});
    brute.load("Ball", "Ball", RBPcollision());
    rdc.load("Ball", "Ball", RBPcollision());

}

void LauncherState::draw() const
{
    cam.use();

    Game::instance()->drawObjects();

    floor.draw();

}

void LauncherState::reset()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);



    glViewport(0,0,DisplayManager::instance()->getSize().first,DisplayManager::instance()->getSize().second);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, static_cast<float>(DisplayManager::instance()->getSize().first)/static_cast<float>(DisplayManager::instance()->getSize().second), 0.1, 10000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();



    GLfloat light_direction[] = {15, 50, 15, 1};
    GLfloat ambientL[] = {0.3f,0.3f,0.3f,1};
    GLfloat diffuseL[] = {1,1,1,1};
    GLfloat specularL[] = {0,0,0,1};


    glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientL);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseL);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularL);

    glClearColor(0, 0, 0, 1);

}

int LauncherState::update()
{
    SDLEventHandler::update();

    Game::instance()->updateObjects();

//    //brute.update(Game::iterator(/*"Ball",ObjIterator::ALL*/));
    rdc.update(Game::iterator(/*"Ball",ObjIterator::ALL*/));
    cam.update();

    return ret;
}



void LauncherState::onJoyButtonEvent(const SDL_JoyButtonEvent& e)
{
    if (e.type == SDL_JOYBUTTONDOWN)
    {
         ret = -1;
    }
}

void LauncherState::onKeyboardEvent(const SDL_KeyboardEvent &e)
{
    if (e.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYDOWN)
    {
        ret = -1;
    }
    else
    {
        auto velocity = 400.f;
        auto v = cam.Velocity();


        if (e.keysym.sym == SDLK_LEFT)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(velocity, v.Y(), v.Z()) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel( Vec3f(0, v.Y(), v.Z()) );
                }
            }
        }
        if (e.keysym.sym == SDLK_RIGHT)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(-velocity, v.Y(), v.Z()) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel( Vec3f(0, v.Y(), v.Z()) );
                }
            }
        }
        if (e.keysym.sym == SDLK_DOWN)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(v.X(), -velocity, v.Z()) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel(Vec3f(v.X(), 0, v.Z()));
                }
            }
        }
        if (e.keysym.sym == SDLK_UP)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(v.X(), velocity, v.Z()) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel(Vec3f(v.X(), 0, v.Z()) );
                }
            }
        }

        if (e.keysym.sym == SDLK_a)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(-velocity, v.Y(), v.Z()) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel( Vec3f(0, v.Y(), v.Z()) );
                }
            }
        }
        if (e.keysym.sym == SDLK_d)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(velocity, v.Y(), v.Z()) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel( Vec3f(0, v.Y(), v.Z()) );
                }
            }
        }
        if (e.keysym.sym == SDLK_s)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(v.X(), v.Y(), -velocity) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel(Vec3f(v.X(), v.Y(), 0));
                }
            }
        }
        if (e.keysym.sym == SDLK_w)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(v.X(), v.Y(), velocity) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel(Vec3f(v.X(), v.Y(), 0));
                }
            }
        }
        if (e.keysym.sym == SDLK_q)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(v.X(), -velocity, v.Z()) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel(Vec3f(v.X(), 0, v.Z()));
                }
            }
        }
        if (e.keysym.sym == SDLK_e)
        {
            if(e.type == SDL_KEYDOWN)
            {
                cam.setVel( Vec3f(v.X(), velocity, v.Z()) );
            }
            else
            {
                if(e.type == SDL_KEYUP)
                {
                    cam.setVel(Vec3f(v.X(), 0, v.Z()));
                }
            }
        }

    }
}

void LauncherState::onMouseButtonEvent(const SDL_MouseButtonEvent &e)
{
    if (e.button == SDL_BUTTON_RIGHT && e.type == SDL_MOUSEBUTTONUP)
    {
        ret = -1;
    }
    if (e.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP)
    {
        static constexpr float launchforce = 300.f;
        Ray r = cam.traceRay(e.x, e.y);
        Ball* b = new Ball(cam.Position(), r.Direction()*launchforce);
        b->setRadius(30);
        Game::instance()->addObject(b);

    }
    if (e.button == SDL_BUTTON_MIDDLE  && e.type == SDL_MOUSEBUTTONUP)
    {


    }
}

void LauncherState::ballsTouchedSoGay(GameObject* a, GameObject* b) noexcept
{
    dynamic_cast<Ball*>(a)->setColour(GLRGBColour(0.8f,0.2f,0.7f));
    dynamic_cast<Ball*>(b)->setColour(GLRGBColour(0.8f,0.2f,0.7f));
}
