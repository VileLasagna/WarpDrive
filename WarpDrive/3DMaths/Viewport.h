#ifndef VIEWPORT_H
#define VIEWPORT_H


#ifdef WIN32
    #include <windows.h>
#endif //WIN32

#include "BaseMaths/Vec2.h"
#include "Display/Camera.h"
#include <GL/gl.h>
//TODO:  Source File to be written

class Viewport
{
public:

	Viewport();
	Viewport(Vec2i LowerLeft, Vec2i dimensions, Vec2f ClippingPlanes = Vec2f(0.00001,10000000000)/*By default you see forever*/, float FoV = 45);
	void setForDraw();
	void resize (Vec2i LowerLeft, Vec2i dimensions);
	void setViewVolume(Vec2f ClippingPlanes, float FoV, float AspectRatio = -1 /*-1 aspect ratio means automatic get it from the viewport dimensions*/);

private:

	float viewAspect; // w/h
	float Near;
	float Far;
	float FoV;
	Camera* camera;


};



#endif //VIEWPORT_H