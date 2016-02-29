#ifndef BRICK_H
#define BRICK_H

#include "basesystem/GameObject.h"
#include "3DMaths/Material.h"
#include "Display/Texture.h"
#include "3DMaths/GLMesh.h"


class Brick: public GameObject
{
public:

	Brick(Vec3f P = Vec3f(0,0,0));
	void Update();
	void Draw();
	void setMaterial(Material* M);
	void setTexture(Texture* T);
	int getState(); //0 = falling, 1 = stationary, 2 = vanishing, 3 = absolutelydead
	void settle();
	void kill();
	const char* getType() const {return "brick";}


private:

	static GLMesh* getCube();
	int state;



};



#endif //BRICK_H
