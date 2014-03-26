#include "BaseSystem/TeapotLoaderState.h"
#ifdef WIN32
    #include <windows.h>
#endif //WIN32
#include "GL/glut.h"



TeapotLoaderState::TeapotLoaderState()
{
   self = 0;
   ret = self;
   pots.push_back(new Teapot);
   cam.setTarget(pots.front());
   cam.setPos(Vec3f(0,0,10));
   cam.Use();
   //glutInit(0, NULL);

}

int TeapotLoaderState::Update()
{

    return self;
}


void TeapotLoaderState::Draw()
{

    for(Teapot* p: pots)
    {
        p->Draw();
    }


}


void TeapotLoaderState::Reset()
{

}
