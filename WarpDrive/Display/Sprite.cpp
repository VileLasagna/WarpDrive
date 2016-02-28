
#include "Display/Sprite.hpp"
#include <algorithm>


Sprite::Sprite(const std::string& filename)

{
	vel = Vec2f(0,0);
	accel = Vec2f(0,0);
	pos = Vec2f(0,0);
	current = Vec2i(-1,-1);
	currentCell = Vec2i(0,0);
	dt = 0;
	transpThreshold = 128;
	if (StringProc::equalsIgnoreCase (filename.substr(filename.size()-10), ".sheetlist"))
	{
		std::ifstream infile;
		infile.open(filename.c_str());
		assert(infile);
		std::string line;
		int st = 0;
		while (std::getline(infile, line))
		{
			if( StringProc::trim(&line) && (line.at(0) != '#') )
			{
				if(line.length() > 0)
				{
					AnimSheet* as = new AnimSheet(line);
					sheets.push_back(as);
					sheets[st]->setAlphaT(transpThreshold);
					std::vector <std::pair<Vec2<Vec2i>,int> > tempAnims = sheets[st]->getAnims();
					for (unsigned int i = 0; i < tempAnims.size(); i++)
					{
						animations.push_back(std::pair<Vec3<Vec2i>,int>( Vec3<Vec2i> ( Vec2i(st,i), tempAnims[i].first.X() , tempAnims[i].first.Y() ), tempAnims[i].second  ));
					}
					st++;
				}
			}
		}
		baseSize = sheets[0]->getSize();
		infile.close();
		this->setCellTime();
	}
	else
	{
		AnimSheet* as = new AnimSheet(filename);
		sheets.push_back(as);
		sheets[0]->setAlphaT(transpThreshold);
		baseSize = sheets[0]->getSize();
		std::vector<std::pair<Vec2<Vec2i>,int> > tempAnims = sheets[0]->getAnims();
		for (unsigned int i = 0; i < tempAnims.size(); i++)
		{
			animations.push_back( std::pair< Vec3<Vec2i>, int>( Vec3<Vec2i>(Vec2i(0,i), tempAnims[i].first.X() , tempAnims[i].first.Y() ), tempAnims[i].second ) );
		}
		this->setCellTime();

	}
	
}

void Sprite::setCellTime(float secs)
{
	maxCellTime = secs;
}


int Sprite::playAnimation(int i)
{
	i -= 1; //internally, indexes start at 0;
    float dts = DisplayManager::instance()->getDtSecs(); //note: It does NOT update this value, this must be done before the "update round" for everything is done
	dt += dts;
	// Update velocity and position
    Vec2f u =  vel;
    vel += accel * dts;
    pos += (vel + u) * (dts * 0.5f);
	
	if (i == current.X())
	{
		// Update bounding rect
		rect = Rectf(
        pos.X(), 
		pos.X() + sheets[animations[current.X()].first.X().X()]->getSize().X(),
        pos.Y(),
        pos.Y() + sheets[animations[current.X()].first.X().X()]->getSize().Y());
		if (currentCell != animations[i].first.Z())//not the last frame in the animation
		{
			if (dt >= maxCellTime)
			{
			currentCell = sheets[animations[current.X()].first.X().X()]->nextSprite(currentCell);
			current = Vec2i(current.X(),current.Y()+1);
			dt = 0;
			}
		}
		else
		{
			if (animations[i].second != (-1)) //This animation transitions to another one
			{
						int numAnims = 0;
						for (int j = 0; j < animations[i].first.X().X(); j++)
						{
							numAnims+= sheets[animations[j].first.X().X()]->getAnims().size();
						}
						current = Vec2i(animations[i].second+numAnims,0);
						currentCell = animations[current.X()].first.Y();
						// Update bounding rect
						rect = Rectf(
						pos.X(), 
						pos.X() + sheets[animations[current.X()].first.X().X()]->getSize().X(),
						pos.Y(),
						pos.Y() + sheets[animations[current.X()].first.X().X()]->getSize().Y());
						sheets[animations[current.X()].first.X().X()]->setAlphaT(transpThreshold);
						dt = 0;
			}
			else
			{
				currentCell = animations[i].first.Y();
				current.setY(0);
				dt = 0;
			}
		}
	}
	else
	{//new animation
		current = Vec2i(i,0);
		currentCell = animations[i].first.Y();
		// Update bounding rect
		rect = Rectf(
        pos.X(), 
		pos.X() + sheets[animations[current.X()].first.X().X()]->getSize().X(),
        pos.Y(),
        pos.Y() + sheets[animations[current.X()].first.X().X()]->getSize().Y());
		sheets[animations[current.X()].first.X().X()]->setAlphaT(transpThreshold);
		dt = 0;
	}   
	return current.X()+1;
}

void Sprite::setDrawAlpha(int alpha)
{
	for(unsigned int i = 0; i < sheets.size(); i++)
	{
        sheets[i]->setDrawAlpha(alpha);
	}
}

void Sprite::setColourKey(const SDLRGBColour& tc)
{
	for(unsigned int i = 0; i < sheets.size(); i++)
	{
		sheets[i]->setColourKey(tc);
	}
}

void Sprite::Draw()
{
	if (current.X() == -1) {return;} //this method has been called before the sprite was updated for the first time. Ignore the mistake
	int ax = sheets[animations[current.X()].first.X().X()]->getAdjust().X();
	int ay = sheets[animations[current.X()].first.X().X()]->getAdjust().Y();
	Vec2i apos;//the position adjusted by any offset this sheet might have.
	apos.setX( (int)pos.X() + ax);
	apos.setY( (int)pos.Y() + ay);
	sheets[animations[current.X()].first.X().X()]->Blit(currentCell, (int)apos.X(), (int)apos.Y());
}

void Sprite::setPos(const Vec2f& p)
{
	pos = p;
	rect = Rectf(pos.X(), pos.X()+baseSize.X(), pos.Y(), pos.Y()+baseSize.Y());
}


    
bool Sprite::pixCollision(const Sprite& other) const
{
	// If bounding rectangles do not intersect, sprites
    //  do not collide
	if (!rect.intersects(other.getBox()))
    {
        return false;
    }
	else
	{
		Rectf inter = intersection(other.getBox());
		 // Loop over region
		int height = (int)(inter.Height());
		int width = (int)(inter.Width());

		int xOff = (int)(inter.MinX() - pos.X());
		int xOffOther = (int)(inter.MinX() - other.getPos().X());

		int yOff = (int)(inter.MinY() - pos.Y());
		int yOffOther = (int)(inter.MinY() - other.getPos().Y());

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// If pixel in current cell at (i, j) is non-transparent
				//  for both sprites, then they do intersect
				bool thisIsTransparent = sheets[animations[current.X()].first.X().X()]->isPixTransparent(
					currentCell, j + xOff, i + yOff);
				bool otherIsTransparent = other.getSheet().isPixTransparent(
					other.currentCell, j + xOffOther, i + yOffOther);

				if (!thisIsTransparent && !otherIsTransparent)
				{
					return true;
				}
			}
		}
		// All pixels in region checked, there is no intersection
		return false;
	}
}

bool Sprite::pixCollision(const SDLImage& other) const
{
	// If bounding rectangles do not intersect, sprites
    //  do not collide
	if (!rect.intersects(other.getBox()))
    {
        return false;
    }
	else
	{
		Rectf inter = intersection(other.getBox());
		 // Loop over region
		int height = (int)(inter.Height());
		int width = (int)(inter.Width());

		int xOff = (int)(inter.MinX() - pos.X());
		int xOffOther = (int)(inter.MinX() - other.getPos().X());

		int yOff = (int)(inter.MinY() - pos.Y());
		int yOffOther = (int)(inter.MinY() - other.getPos().Y());

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// If pixel in current cell at (i, j) is non-transparent
				//  for both sprites, then they do intersect
				bool thisIsTransparent = sheets[animations[current.X()].first.X().X()]->isPixTransparent(
					currentCell, j + xOff, i + yOff);
				bool otherIsTransparent = other.isPixTransparent(i+xOffOther,j+yOffOther);

				if (!thisIsTransparent && !otherIsTransparent)
				{
					return true;
				}
			}
		}
		// All pixels in region checked, there is no intersection
		return false;
	}
}

Rectf Sprite::intersection(const Rectf &box) const
{
    if (!rect.intersects(box))
    {
        return Rectf();
    }
	else
	{
		return Rectf(
		  std::max(rect.MinX(), box.MinX()),   // Min X
		  std::min(rect.MaxX(), box.MaxX()),   // Max X
		  std::max(rect.MinY(), box.MinY()),   // Min Y
		  std::min(rect.MaxY(), box.MaxY()) ); // Max Y
	}
}
