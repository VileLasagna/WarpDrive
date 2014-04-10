#include "BaseSystem/TeapotLoaderState.h"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include "GL/glut.h"



TeapotLoaderState::TeapotLoaderState()
{
   self = 0;
   ret = self;
   Reset();
   pots.push_back(new Sphere(0, 0, 0, 3));
   cam.setTarget(pots.front()->getCentre());
   cam.setPos(Vec3f(0,0,20));
   cam.Use();
   //glutInit(0, NULL);

}



void TeapotLoaderState::Draw()
{

    for(Sphere* p: pots)
    {
        p->Draw();
    }


}


void TeapotLoaderState::Reset()
{
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

}

int TeapotLoaderState::Update()
{
    SDLEventHandler::Update();

    cam.Update();
    cam.Use();

    return ret;
}



void TeapotLoaderState::onJoyButtonEvent(const SDL_JoyButtonEvent& e)
{
    if (e.type == SDL_JOYBUTTONDOWN)
    {
         ret = -1;
    }
}

void TeapotLoaderState::onKeyboardEvent(const SDL_KeyboardEvent &e)
{
    if (e.keysym.sym == SDLK_ESCAPE && e.type == SDL_KEYDOWN)
    {
        ret = -1;
    }
    else
    {


    }
}

void TeapotLoaderState::onMouseButtonEvent(const SDL_MouseButtonEvent &e)
{
    if (e.button == SDL_BUTTON_RIGHT)
    {
        ret = -1;
    }
    if (e.button == SDL_BUTTON_LEFT)
    {
        cam.orbit(1,0,1, 20, 2);
    }
}
