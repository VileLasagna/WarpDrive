#include "Brick.h"
#include <GL/glu.h>
#include "Events/TimedRemoveEvent.h"


Brick::Brick(Vec3f P)
{

        removeMe = false;
        pos = P;

}


void Brick::Update()
{

        GameObject::Update();

}

void Brick::Draw()
{
        glPushMatrix();

                glTranslatef(pos.X(),pos.Y(),pos.Z());
                Brick::getCube()->Draw();

        glPopMatrix();

}


GLMesh* Brick::getCube()
{
        static GLMesh* CUBE = new GLMesh("data/Brick.obj", true, false, false);
        static bool b = CUBE->setSize(1.2);
        return CUBE;

}

void Brick::kill()
{

        //run away, timed kill event
        vel = Vec3f(0,-5,-5);
        addEvent(new TimedRemoveEvent(15));

};
