#include "Grid.h"
#include "BaseSystem/Game.h"
#include "Events/TimedMoveEvent.h"
#include "Display/Texture.h"
#include "Sound/SoundManager.h"
#include "Sound/SoundFX.h"
#include <GL/glut.h>


Grid::Grid()
{
	Reset();
	spinfx = new SoundFX(SoundManager::instance()->loadSound("data/spin.wav"));
	dropfx = new SoundFX(SoundManager::instance()->loadSound("data/drop.wav"));
	linefx = new SoundFX(SoundManager::instance()->loadSound("data/line.wav"));
	failfx = new SoundFX(SoundManager::instance()->loadSound("data/failed.wav"));
	linecount = 0;
	
}

void Grid::Reset()
{
	setSize();
	current = 0;
	Game::iterator it = Game::iterator("brick");
	if(!it.isEmpty())
	{
		do
		{
			Game::instance()->removeDrawnObject(it);
			Game::instance()->removeActiveObject(it);
		}
		while(it.Next());
	}
	removeMe = false;
}

bool Grid::GameOver()
{
	bool ret = false;
	for(int j = 0; j < W; j++)
	{
		if( GD[((H-1)*W)+j] ) //any brick on the top row
		{
			ret = true;
		}
	}
	return ret;
}

void Grid::Update()
{
	if(GameOver())
	{
		return;
	}

	if(current)
	{
		current->Update();
		//check for boundaries
		Vec4<Vec2i> blocks = current->getBricks();
		int minX = blocks.X().X();
		int maxX = blocks.X().X();
		if (blocks.Y().X() < minX)
		{
			minX = blocks.Y().X();
		}
		if (blocks.Y().X() > maxX)
		{
			maxX = blocks.Y().X();
		}
		if (blocks.Z().X() < minX)
		{
			minX = blocks.Z().X();
		}
		if (blocks.Z().X() > maxX)
		{
			maxX = blocks.Z().X();
		}
		if (blocks.W().X() < minX)
		{
			minX = blocks.W().X();
		}
		if (blocks.W().X() > maxX)
		{
			maxX = blocks.W().X();
		}
		if (minX < 0)
		{
			current->nudge(-minX,0);
		}
		if (maxX >= W)
		{
			current->nudge((W-maxX)-1,0);
		}

		if(collision())
		{
			
			Brick* b = new Brick(Vec3f(blocks.X().X()*2,blocks.X().Y()*2,0));
			Game::instance()->addObject(b);
			int a = blocks.X().Y()*W+blocks.X().X();
			if(a < GD.size())
			{
				GD[a] = b;
			}
			b = new Brick(Vec3f(blocks.Y().X()*2,blocks.Y().Y()*2,0));
			Game::instance()->addObject(b);
			a = blocks.Y().Y()*W+blocks.Y().X();
			if(a < GD.size())
			{
				GD[a] = b;
			}
			b =  new Brick(Vec3f(blocks.Z().X()*2,blocks.Z().Y()*2,0));
			Game::instance()->addObject(b);
			a = blocks.Z().Y()*W+blocks.Z().X();
			if(a < GD.size())
			{
				GD[a] = b;
			}
			b =  new Brick(Vec3f(blocks.W().X()*2,blocks.W().Y()*2,0));
			Game::instance()->addObject(b);
			a = blocks.W().Y()*W+blocks.W().X();
			if(a < GD.size())
			{
				GD[a] = b;
			}
			delete current;
			current = 0;
			lines();
			if(GameOver())
			{

				SoundManager::instance()->playSound(failfx);
			}
			else
			{
				SoundManager::instance()->playSound(dropfx);
			}
		}

	}
	else
	{
		current = new Tetrad();
		current->setPivot(Vec2i(5,17));
		int lf =  -linecount/7;
		current->setVel(Vec3f(0,-1+lf,0));
		current->setPos(Vec3f(2*5,2*17,0));
	}





}


void Grid::Draw()
{
	Texture::UseNoTexture();
	glPushMatrix();
		glTranslatef(pos.X(),pos.Y(),pos.Z());
		//0,0 is bottom left
		for(int i = 0; i < H; i++)
		{
			for (int j = 0; j < W; j++)
			{
				glPushMatrix();
					glTranslatef(j*2,i*2,0);
					glutWireCube(2);
				glPopMatrix();
			}
		}

		if(current)
		{
			glPushMatrix();

				glTranslatef(current->getPivot().X()*2,current->getPos().Y(),0);
				current->Draw();

			glPopMatrix();
		}
	glPopMatrix();

}

void Grid::setSize(int w, int h)
{
	W = w;
	H = h;
	GD.clear();
	for(int i = 0; i < H; i++)
	{
		for(int j = 0; j < W; j++)
		{
			GD.push_back(0);
		}
	}
}

void Grid::spin()
{
	if(GameOver())
	{
		return;
	}

	if (current)
	{
		SoundManager::instance()->playSound(spinfx);
		current->spin();
	}
}

void Grid::nudge(bool left)
{
	if(GameOver())
	{
		return;
	}

	if (!current)
	{
		return;
	}
	if(!canNudge(left))
	{
		return;
	}
	if (left)
	{
		current->nudge(-1,0);
	}
	else
	{
		current->nudge(1,0);
	}
}

void Grid::drop()
{
	if(GameOver())
	{
		return;
	}

	while(!collision())
	{
		current->nudge(0,-1);
	}
}

bool Grid::collision()
{
	bool ret = false;
	if(!current)
	{
		return false;
	}
	Vec4<Vec2i> blocks = current->getBricks();
	if(blocks.X().Y() < H && (blocks.X().Y() == 0 || GD[((blocks.X().Y()-1)*W)+blocks.X().X()]))
	{
		ret = true;
	}
	if(blocks.Y().Y() < H && (blocks.Y().Y() == 0 || GD[((blocks.Y().Y()-1)*W)+blocks.Y().X()]))
	{
		ret = true;
	}
	if(blocks.Z().Y() < H && (blocks.Z().Y() == 0 || GD[((blocks.Z().Y()-1)*W)+blocks.Z().X()]))
	{
		ret = true;
	}
	if(blocks.W().Y() < H && (blocks.W().Y() == 0 || GD[((blocks.W().Y()-1)*W)+blocks.W().X()]))
	{
		ret = true;
	}



	return ret;
}

bool Grid::canNudge(bool left)
{

	bool ret = true;
	if(!current)
	{
		return false;
	}
	int direction = 1;
	if(left)
	{
		direction = -1;
	}
	Vec4<Vec2i> blocks = current->getBricks();
	if(blocks.X().Y() < H && (blocks.X().X()+direction > 0) && (blocks.X().X() + direction < (W-1)) && GD[((blocks.X().Y())*W)+blocks.X().X()+direction])
	{
		ret = false;
	}
	if(blocks.Y().Y() < H && (blocks.Y().X()+direction > 0) && (blocks.Y().X() + direction < (W-1)) && GD[((blocks.Y().Y())*W)+blocks.Y().X()+direction])
	{
		ret = false;
	}
	if(blocks.Z().Y() < H && (blocks.Z().X()+direction > 0) && (blocks.Z().X() + direction < (W-1)) && GD[((blocks.Z().Y())*W)+blocks.Z().X()+direction])
	{
		ret = false;
	}
	if(blocks.W().Y() < H && (blocks.W().X()+direction > 0) && (blocks.W().X() + direction < (W-1)) && GD[((blocks.W().Y())*W)+blocks.W().X()+direction])
	{
		ret = false;
	}

	return ret;


}

void Grid::lines()
{
	int rows = 0;
	for(int i = 0; i < H; i++)
	{
		int c = 0;
		for(int j = 0; j < W; j++)
		{
			if(GD[i*W+j] != 0)
			{
				c++;
			}
		}
		if (c == W)
		{
			for(int j = 0; j < W; j++)
			{
				if(GD[i*W+j])
				{
					GD[i*W+j]->kill();
					GD[i*W+j] = 0;
				}
			}
			rows++;
			linecount++;
		}
		else
		{
			if(rows)
			{
				for(int j = 0; j < W; j++)
				{
					if(GD[i*W+j])
					{
						//move brick down X rows
						GD[(i-rows)*W+j] = GD[(i)*W+j];
						GD[i*W+j]->addEvent(new TimedMoveEvent(0.3*rows,Vec3f(0,-2*rows,0)));
						GD[i*W+j] = 0;
					}
				}
			}
		}

	}
	if(rows)
	{
		SoundManager::instance()->playSound(linefx);
	}
}

