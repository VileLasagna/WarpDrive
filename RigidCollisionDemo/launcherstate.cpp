#include "launcherstate.hpp"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include "GL/glu.h"
#include<string>

#include "WarpDrive/BaseMaths/Sphere.hpp"

LauncherState::LauncherState()
   :floor(Vec3f(0,1,0),0)
{
   self = 0;
   ret = self;
   Reset();
//   pots.push_back(new Sphere(0, 0, 0, 2));

//   pots.push_back(new Sphere(3, 6, 4, 2));
//   pots.push_back(new Sphere(-2, 4, 0, 1));
//   pots.push_back(new Sphere(6, 3.5, 7, 2));
//   pots.push_back(new Sphere(-3, -10, -10, 2));
//   pots.push_back(new Sphere(-10, -4, 0, 4));
//   pots.push_back(new Sphere(-6, 3.5, -2.5, 1));

//   for(Sphere* p: pots)
//   {
//       p->setWireframe(false);
//   }

   cam.setTarget(Vec3f(0,0,0));
   cam.setPos(Vec3f(0,400,-700));
   cam.Use();
   floor.DrawAsWireframe(true);
   floor.setDrawn(100,100,60);
   floor.DrawNormal(true);

   balls.push_back(new Ball());
   balls[0]->setRadius(30);
   balls[0]->setPos(Vec3f(0,400,0));
   balls[0]->setVel(Vec3f(0,0,300));

}



void LauncherState::Draw()
{

    for(Ball* b: balls)
    {
        b->Draw();
    }

    floor.Draw();

}


void LauncherState::Reset()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);



    glViewport(0,0,DisplayManager::instance()->getSize().first,DisplayManager::instance()->getSize().second);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)(DisplayManager::instance()->getSize().first)/(float)(DisplayManager::instance()->getSize().second), 0.1, 10000.0);
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

int LauncherState::Update()
{
    SDLEventHandler::Update();

    for(Ball* b: balls)
    {
        b->Update();
    }

    cam.Update();
    cam.Use();

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
        auto v = cam.getVel();

        if (e.keysym.sym == SDLK_LEFT)
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
        if (e.keysym.sym == SDLK_RIGHT)
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

    }
}

void LauncherState::onMouseButtonEvent(const SDL_MouseButtonEvent &e)
{
//    if (e.button == SDL_BUTTON_RIGHT && e.type == SDL_MOUSEBUTTONUP)
//    {
//        ret = -1;
//    }
//    if (e.button == SDL_BUTTON_LEFT && e.type == SDL_MOUSEBUTTONUP)
//    {
//        for(Sphere* p: pots)
//        {
//            p->setColour(1, 1, 1);
//        }

//        GLdouble x, y, z;
//        GLfloat winZ;
//        x = 0;
//        y = 0;
//        z = 0;
//        winZ = 0;
//        GLdouble model[16] /*= {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}*/;
//        GLdouble proj[16];
//        GLint viewport[4];

//        glGetDoublev(GL_MODELVIEW_MATRIX,model);

//        glGetDoublev(GL_PROJECTION_MATRIX,proj);
//        glGetIntegerv(GL_VIEWPORT,viewport);


//        glReadPixels(e.x, viewport[3] - e.y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);


//       auto res = gluUnProject(e.x,viewport[3] - e.y, winZ , model, proj, viewport, &x,&y,&z);


//        if (res == GL_FALSE)
//        {
//          //assert(0);
//        }

//        glPointSize(10);
//        glBegin(GL_POINTS);
//        glColor3f(1, 0, 0);
//            glVertex3f(x, y, z);
//        glEnd();


//        std::string title = "Screen X Y Z: "+ std::to_string(e.x)+" " + std::to_string(e.y) + " " +  std::to_string(winZ) +
//                " // World X Y Z: "+ std::to_string(x)+" " + std::to_string(y) + " " +  std::to_string(z);
//        DisplayManager::instance()->setTitle(title);
//        //pots.push_back(new Sphere(4, 0, 0, 1));

//        Vec3f point (x,y,z);

//        for(Sphere* p: pots)
//        {
//            auto trace = point - p->getCentre();
//            if( trace.sqMod() <= p->getRadius()*p->getRadius() )
//            {
//                p->setColour(0, 1, 0.5f);
//            }
//            else
//            {
//                p->setColour(1,1,1);
//            }
//        }

//    }
//    if (e.button == SDL_BUTTON_MIDDLE  && e.type == SDL_MOUSEBUTTONUP)
//    {
//        for(Sphere* p: pots)
//        {
//            //p->setColour(1,0,1);
//            p->setWireframe(!p->getWireframe());
//        }

//    }
}
