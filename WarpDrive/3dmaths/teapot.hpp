#ifndef WD_TEAPOT_HPP_DEFINED
#define WD_TEAPOT_HPP_DEFINED


#include "basesystem/gameobject.hpp"
#include "physics/alignedboundingbox.hpp"
#include "display/texture.hpp"

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
    void update() override
	{
        GameObject::update();
		vel+= accel*DisplayManager::instance()->getDtSecs(); 
		pos+= vel*DisplayManager::instance()->getDtSecs();
        float halfsize = size*1.3f;
        BoundingBox = AABBox(pos.X()-halfsize,pos.X()+halfsize,pos.Y()-halfsize,pos.Y()+halfsize,pos.Z()-halfsize,pos.Z()+halfsize);
		type = "Teapot";
	}
    void draw() const override
	{
        if(tex)
		{
            tex->useThisTexture();
		}
		else
		{
            Texture::useNoTexture();
		}
		glDisable(GL_LIGHTING);
        BoundingBox.draw();
		glEnable(GL_LIGHTING);
		glPushMatrix();
			glTranslatef(pos.X(),pos.Y(),pos.Z());
            //glutSolidTeapot(size);
		glPopMatrix();
        glEnd();
	}
	void setSize(float s){size = s;}
	void setTex(Texture* T) {tex = T;}

private:

	float size;
	Texture* tex;
    AABBox BoundingBox;



};
#endif //WD_TEAPOT_HPP_DEFINED
