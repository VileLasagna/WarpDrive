#ifndef TEAPOTLOADERSTATE_H
#define TEAPOTLOADERSTATE_H

#include "BaseSystem/GameState.h"
#include "3DMaths/Teapot.h"
#include <vector>
#include "Display/Camera.h"


class TeapotLoaderState : public GameState
{
public:


	TeapotLoaderState();

	int Update();
	void Draw();
	void Reset();



	~TeapotLoaderState(){};


private:


    std::vector<Teapot*> pots;
    Camera cam;





};


#endif //TEAPOTLOADERSTATE_H
