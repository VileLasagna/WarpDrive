#include "WarpDrive/display/sprite.hpp"

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
        unsigned int st = 0;
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
                        animations.push_back(std::pair<Vec3<Vec2i>,int>( Vec3<Vec2i> ( Vec2i(static_cast<int>(st),static_cast<int>(i)),
                                                                                       tempAnims[i].first.X() , tempAnims[i].first.Y() ),
                                                                         tempAnims[i].second  ));
					}
					st++;
				}
			}
		}
        baseSize = sheets[0]->CellSize();
		infile.close();
		this->setCellTime();
	}
	else
	{
		AnimSheet* as = new AnimSheet(filename);
		sheets.push_back(as);
		sheets[0]->setAlphaT(transpThreshold);
        baseSize = sheets[0]->CellSize();
		std::vector<std::pair<Vec2<Vec2i>,int> > tempAnims = sheets[0]->getAnims();
		for (unsigned int i = 0; i < tempAnims.size(); i++)
		{
            animations.push_back( std::pair< Vec3<Vec2i>, int>( Vec3<Vec2i>(Vec2i(0,static_cast<int>(i)),
                                                                            tempAnims[i].first.X() ,
                                                                            tempAnims[i].first.Y() ),
                                                                tempAnims[i].second ) );
		}
		this->setCellTime();

	}
	
}

void Sprite::setCellTime(float secs)
{
    maxCellTime = static_cast<int64_t>(secs * 1000);
}

int Sprite::playAnimation(int i)
{
	i -= 1; //internally, indexes start at 0;
    auto dts = DisplayManager::instance()->Dt();
	dt += dts;
	// Update velocity and position
    Vec2f u =  vel;
    vel += accel * (dts * 0.001f);
    pos += (vel + u) * (dts * 0.5f * 0.001f );
	
	if (i == current.X())
	{
		// Update bounding rect
		rect = Rectf(
        pos.X(), 
        pos.X() + sheets[static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->CellSize().X(),
        pos.Y(),
        pos.Y() + sheets[static_cast<size_t>(animations[static_cast<size_t>(current.X())].first.X().X())]->CellSize().Y());
        if (currentCell != animations[static_cast<size_t>(i)].first.Z())//not the last frame in the animation
		{
			if (dt >= maxCellTime)
			{
                currentCell = sheets[ static_cast<size_t>(animations[static_cast<size_t>(current.X())].first.X().X()) ]->nextSprite(currentCell);
                current = Vec2i(current.X(),current.Y()+1);
                dt = 0;
			}
		}
		else
		{
            if (animations[static_cast<size_t>(i)].second != (-1)) //This animation transitions to another one
			{
						int numAnims = 0;
                        for (int j = 0; j < animations[static_cast<size_t>(i)].first.X().X(); j++)
						{
                            numAnims+= sheets[ static_cast<size_t>(animations[static_cast<size_t>(j)].first.X().X()) ]->getAnims().size();
						}
                        current = Vec2i(animations[ static_cast<size_t>(i)].second+numAnims,0);
                        currentCell = animations[ static_cast<size_t>(current.X())].first.Y();
						// Update bounding rect
						rect = Rectf(
						pos.X(), 
                        pos.X() + sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->CellSize().X(),
						pos.Y(),
                        pos.Y() + sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->CellSize().Y());
                        sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->setAlphaT(transpThreshold);
						dt = 0;
			}
			else
			{
                currentCell = animations[static_cast<size_t>(i)].first.Y();
				current.setY(0);
				dt = 0;
			}
		}
	}
	else
	{//new animation
		current = Vec2i(i,0);
        currentCell = animations[static_cast<size_t>(i)].first.Y();
		// Update bounding rect
		rect = Rectf(
        pos.X(), 
        pos.X() + sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->CellSize().X(),
        pos.Y(),
        pos.Y() + sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->CellSize().Y());
        sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->setAlphaT(transpThreshold);
		dt = 0;
	}   
	return current.X()+1;
}

void Sprite::setDrawAlpha(unsigned int alpha)
{
	for(unsigned int i = 0; i < sheets.size(); i++)
	{
        sheets[i]->setDrawAlpha( static_cast<Uint8>(alpha) );
	}
}

void Sprite::setColourKey(const SDLRGBColour& tc)
{
	for(unsigned int i = 0; i < sheets.size(); i++)
	{
		sheets[i]->setColourKey(tc);
	}
}

void Sprite::draw()
{
	if (current.X() == -1) {return;} //this method has been called before the sprite was updated for the first time. Ignore the mistake
    int ax = sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->Adjust().X();
    int ay = sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->Adjust().Y();
	Vec2i apos;//the position adjusted by any offset this sheet might have.
    apos.setX( static_cast<int>(pos.X()) + ax);
    apos.setY( static_cast<int>(pos.Y()) + ay);
    sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->blit(currentCell,
                                                                                                      static_cast<int>(apos.X()),
                                                                                                      static_cast<int>(apos.Y()) );
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
    if (!rect.intersects(other.Box()))
    {
        return false;
    }
	else
	{
        Rectf inter = intersection(other.Box());
		 // Loop over region
        int height = static_cast<int>(inter.Height());
        int width = static_cast<int>(inter.Width());

        int xOff = static_cast<int>(inter.MinX() - pos.X());
        int xOffOther = static_cast<int>(inter.MinX() - other.Position().X());

        int yOff = static_cast<int>(inter.MinY() - pos.Y());
        int yOffOther = static_cast<int>(inter.MinY() - other.Position().Y());

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// If pixel in current cell at (i, j) is non-transparent
				//  for both sprites, then they do intersect
                bool thisIsTransparent = sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->isPixTransparent(
					currentCell, j + xOff, i + yOff);
                bool otherIsTransparent = other.Sheet().isPixTransparent(
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
    if (!rect.intersects(other.Box()))
    {
        return false;
    }
	else
	{
        Rectf inter = intersection(other.Box());
		 // Loop over region
        int height = static_cast<int>(inter.Height());
        int width = static_cast<int>(inter.Width());

        int xOff = static_cast<int>(inter.MinX() - pos.X());
        int xOffOther = static_cast<int>(inter.MinX() - other.Position().X());

        int yOff = static_cast<int>(inter.MinY() - pos.Y());
        int yOffOther = static_cast<int>(inter.MinY() - other.Position().Y());

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				// If pixel in current cell at (i, j) is non-transparent
				//  for both sprites, then they do intersect
                bool thisIsTransparent = sheets[ static_cast<size_t>(animations[ static_cast<size_t>(current.X()) ].first.X().X()) ]->isPixTransparent(
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
