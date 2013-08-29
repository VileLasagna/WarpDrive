#ifndef BRICK_H
#define BRICK_H

#include "GameObject.h"
#include "Material.h"
#include "Texture.h"
#include "GLMesh.h"


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