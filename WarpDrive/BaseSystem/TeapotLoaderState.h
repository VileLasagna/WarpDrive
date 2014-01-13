#ifndef TEAPOTLOADERSTATE_H
#define TEAPOTLOADERSTATE_H

#include "BaseSystem/GameState.h"
#include "3DMaths/Teapot.h"
#include <vector>

class TeapotLoaderState : public GameState
{
public:


	TeapotLoaderState();

	int Update();
	void Draw();
	void Reset();



	~TeapotLoaderState(){};


private:


	std::vector<Teapot> pots;




};


#endif //TEAPOTLOADERSTATE_H
