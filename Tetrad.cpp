#include "Tetrad.h"


Tetrad::Tetrad()
{
	type = rand()%7;
	pivot = Vec2i(-1,-1); //this means: outside the field
	orient = rand()%4;


}

void Tetrad::Update()
{
	if (pivot == Vec2i(-1,-1))
	{
		//inactive piece is inactive
		return;
	}
	GameObject::Update();
	if ((pivot.Y()*2) - pos.Y() >0.85)
	{
		pivot -= Vec2i(0,1);
	}
}

Vec4<Vec2i> Tetrad::getBricks()
{
	Vec4<Vec2i> ret;
	ret.setW(pivot);
	//Making this into a switch would be even more confusing, as would be creating individual Tetrad classes
	if(type == 0)//cube
	{
		switch(orient)
		{
		case 0: ret.setX(pivot+Vec2i(0,1));ret.setY( pivot+Vec2i(1,1) ); ret.setZ( pivot+Vec2i(1,0) ); break;
		case 1: ret.setX(pivot+Vec2i(1,0));ret.setY( pivot+Vec2i(1,-1) ); ret.setZ( pivot+Vec2i(0,-1) ); break;
		case 2: ret.setX(pivot+Vec2i(0,-1));ret.setY( pivot+Vec2i(-1,-1) ); ret.setZ( pivot+Vec2i(-1,0) ); break;
		case 3: ret.setX(pivot+Vec2i(0,1));ret.setY( pivot+Vec2i(-1,1) ); ret.setZ( pivot+Vec2i(-1,0) ); break;
		}
	}
	if(type == 1)//T
	{
		switch(orient)
		{
		case 0: ret.setX(pivot+Vec2i(-1,0));ret.setY( pivot+Vec2i(1,0) ); ret.setZ( pivot+Vec2i(0,-1) ); break;
		case 1: ret.setX(pivot+Vec2i(-1,0));ret.setY( pivot+Vec2i(0,-1) ); ret.setZ( pivot+Vec2i(0,1) ); break;
		case 2: ret.setX(pivot+Vec2i(0,1));ret.setY( pivot+Vec2i(-1,0) ); ret.setZ( pivot+Vec2i(1,0) ); break;
		case 3: ret.setX(pivot+Vec2i(0,-1));ret.setY( pivot+Vec2i(0,1) ); ret.setZ( pivot+Vec2i(1,0) ); break;
		}
	}
	if(type == 2)//I
	{
		switch(orient)
		{
		case 0: ret.setX(pivot+Vec2i(0,1));ret.setY( pivot+Vec2i(0,-1) ); ret.setZ( pivot+Vec2i(0,-2) ); break;
		case 1: ret.setX(pivot+Vec2i(1,0));ret.setY( pivot+Vec2i(-1,0) ); ret.setZ( pivot+Vec2i(2,0) ); break;
		case 2: ret.setX(pivot+Vec2i(0,-1));ret.setY( pivot+Vec2i(0,1) ); ret.setZ( pivot+Vec2i(0,2) ); break;
		case 3: ret.setX(pivot+Vec2i(1,0));ret.setY( pivot+Vec2i(-1,0) ); ret.setZ( pivot+Vec2i(-2,0) ); break;
		}
	}
	if(type == 3)//L
	{
		switch(orient)
		{
		case 0: ret.setX(pivot+Vec2i(0,1));ret.setY( pivot+Vec2i(1,0) ); ret.setZ( pivot+Vec2i(0,2) ); break;
		case 1: ret.setX(pivot+Vec2i(1,0));ret.setY( pivot+Vec2i(2,0) ); ret.setZ( pivot+Vec2i(0,-1) ); break;
		case 2: ret.setX(pivot+Vec2i(0,-1));ret.setY( pivot+Vec2i(-1,0) ); ret.setZ( pivot+Vec2i(0,-2) ); break;
		case 3: ret.setX(pivot+Vec2i(0,1));ret.setY( pivot+Vec2i(-1,0) ); ret.setZ( pivot+Vec2i(-2,0) ); break;
		}
	}
	if(type == 4)//¬
	{
		switch(orient)
		{
		case 0: ret.setX(pivot+Vec2i(0,-1));ret.setY( pivot+Vec2i(-1,0) ); ret.setZ( pivot+Vec2i(-2,0) ); break;
		case 1: ret.setX(pivot+Vec2i(-1,0));ret.setY( pivot+Vec2i(0,1) ); ret.setZ( pivot+Vec2i(0,2) ); break;
		case 2: ret.setX(pivot+Vec2i(2,0));ret.setY( pivot+Vec2i(0,1) ); ret.setZ( pivot+Vec2i(1,0) ); break;
		case 3: ret.setX(pivot+Vec2i(1,0));ret.setY( pivot+Vec2i(0,-1) ); ret.setZ( pivot+Vec2i(0,-2) ); break;
		}
	}
	if(type == 5)//S
	{
		switch(orient)
		{
		case 0: ret.setX(pivot+Vec2i(-1,0));ret.setY( pivot+Vec2i(0,-1) ); ret.setZ( pivot+Vec2i(-1,1) ); break;
		case 1: ret.setX(pivot+Vec2i(1,1));ret.setY( pivot+Vec2i(0,1) ); ret.setZ( pivot+Vec2i(-1,0) ); break;
		case 2: ret.setX(pivot+Vec2i(0,1));ret.setY( pivot+Vec2i(1,-1) ); ret.setZ( pivot+Vec2i(1,0) ); break;
		case 3: ret.setX(pivot+Vec2i(1,0));ret.setY( pivot+Vec2i(0,-1) ); ret.setZ( pivot+Vec2i(-1,-1) ); break;
		}
	}
	if(type == 6)//Z
	{
		switch(orient)
		{
		case 0: ret.setX(pivot+Vec2i(0,1));ret.setY( pivot+Vec2i(-1,-1) ); ret.setZ( pivot+Vec2i(-1,0) ); break;
		case 1: ret.setX(pivot+Vec2i(-1,1));ret.setY( pivot+Vec2i(0,1) ); ret.setZ( pivot+Vec2i(1,0) ); break;
		case 2: ret.setX(pivot+Vec2i(0,-1));ret.setY( pivot+Vec2i(1,1) ); ret.setZ( pivot+Vec2i(1,0) ); break;
		case 3: ret.setX(pivot+Vec2i(0,-1));ret.setY( pivot+Vec2i(1,-1) ); ret.setZ( pivot+Vec2i(-1,0) ); break;
		}
	}
	return ret;
}

void Tetrad::Draw()
{
	float n = 2;
	//Does NOT set its own drawing position. This is controlled by Grid
	Brick* b = Tetrad::getModel(type);
	glPushMatrix();
	
		b->Draw();
		Vec4<Vec2i> v = getBricks();
		Vec3<Vec2i> rel = Vec3<Vec2i> ( (v.X()-v.W()), (v.Y()-v.W()), (v.Z()-v.W()));
		glPushMatrix();

			glTranslatef(n*rel.X().X(),n*rel.X().Y(),0);
			b->Draw();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(n*rel.Y().X(),n*rel.Y().Y(),0);
			b->Draw();

		glPopMatrix();

		glPushMatrix();

			glTranslatef(n*rel.Z().X(),n*rel.Z().Y(),0);
			b->Draw();

		glPopMatrix();


}

Brick* Tetrad::getModel(int color)
{
	static Brick* BLUE = new Brick();
	return BLUE;
}

void Tetrad::nudge(int h, int v)
{
	if(v!= 0)
	{
		pos = Vec3f(pos.X(),pivot.Y()*2,pos.Z());//reset position
		pos += Vec3f(0,2*v,0);
	}
	pivot += Vec2i(h,v);
}

void Tetrad::spin()
{
	if(orient == 3)
	{
		orient = 0;
	}
	else
	{
		orient++;
	}
}


