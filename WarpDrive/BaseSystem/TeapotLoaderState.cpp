#include "BaseSystem/TeapotLoaderState.h"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include "GL/glut.h"
#include<string>



TeapotLoaderState::TeapotLoaderState()
{
   self = 0;
   ret = self;
   Reset();
   pots.push_back(new Sphere(0, 0, 0, 3));
   //cam.setTarget(pots.front()->getCentre());
   cam.setTarget(Vec3f(0,0,0));
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



    GLfloat light_direction[] = {15, 50, 15, 1};
    GLfloat ambientL[] = {0.1f,0.1f,0.1f,1};
    GLfloat diffuseL[] = {1,1,1,1};
    GLfloat specularL[] = {0,0,0,1};


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
    if (e.button == SDL_BUTTON_RIGHT && e.type == SDL_MOUSEBUTTONUP)
    {
        ret = -1;
    }
    if (e.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP)
    {
        GLdouble x, y, z;
        x = 0;
        y = 0;
        z = 0;
        GLdouble model[16];
        GLdouble proj[16];
        GLint viewport[4];

        glGetDoublev(GL_MODELVIEW,model);
        glGetDoublev(GL_PROJECTION_MATRIX,proj);
        glGetIntegerv(GL_VIEWPORT,viewport);

        int res = gluUnProject(e.x,viewport[3] - e.y,0,model, proj, viewport,&x,&y,&z);
        if (res == GL_FALSE)
        {
            assert(0);
        }

        glPointSize(10);
        glBegin(GL_POINTS);
        glColor3f(1, 0, 0);
            glVertex3f(x, y, z);
        glEnd();


        std::string title = "Unprojected X: "+ std::to_string(x)+"  Unprojected Y: " + std::to_string(y);
        DisplayManager::instance()->setTitle(title);
        //pots.push_back(new Sphere(4, 0, 0, 1));

    }
    if (e.button == SDL_BUTTON_MIDDLE)
    {
        for(Sphere* p: pots)
        {
            p->setColour(1,0,1);
        }

    }
}
