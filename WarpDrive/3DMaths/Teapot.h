#ifndef TEAPOT_H
#define TEAPOT_H


#include "BaseSystem/GameObject.h"
#include "Physics/BoundingBox.h"
#include "Display/Texture.h"

class Teapot: public GameObject
	//generic testing Teapot class
{
public:

	Teapot()
	{
		size = 3; 
		tex = 0; 
		name = "TheTestTeapot";
		type = "Teapot";
	}
	void Update() 
	{
		GameObject::Update();
		vel+= accel*DisplayManager::instance()->getDtSecs(); 
		pos+= vel*DisplayManager::instance()->getDtSecs();
		float halfsize = size*1.3;
		Box = BBox(pos.X()-halfsize,pos.X()+halfsize,pos.Y()-halfsize,pos.Y()+halfsize,pos.Z()-halfsize,pos.Z()+halfsize);
		type = "Teapot";
	}
	void Draw() 
	{
		if(tex)
		{
			tex->UseThisTexture();
		}
		else
		{
			Texture::UseNoTexture();
		}
		glDisable(GL_LIGHTING);
		Box.Draw();
		glEnable(GL_LIGHTING);
		glPushMatrix();
			glTranslatef(pos.X(),pos.Y(),pos.Z());
			glutSolidTeapot(size);
		glPopMatrix();
	}
	void setSize(float s){size = s;}
	void setTex(Texture* T) {tex = T;}

private:

	float size;
	Texture* tex;
	BBox Box;



};
#endif //TEAPOT_H
