
#include "Display/AnimSheet.hpp"
#include <assert.h>




AnimSheet::AnimSheet(std::string filename)
{
	std::ifstream infile;
	infile.open(filename.c_str());
	assert(infile);
	std::string line;
	pass = -1;
	while (std::getline(infile, line) && !(StringProc::equalsIgnoreCase(line, "ENDANIMS")))
	{
		if( StringProc::trim(&line) && (line.at(0) != '#') )
		{
			if(line.length() > 0)
			{
				loadseq(line);
			}
		}
	}
	for (unsigned int i = 0; i < animations.size(); i++)
	{
		animations[i].second = -1;
	}
	if(StringProc::equalsIgnoreCase(line, "ENDANIMS"))//the sheet has transition animations
	{
		while (std::getline(infile, line))
		{
			if( StringProc::trim(&line) && (line.at(0) != '#') )
			{
				Vec2i v = StringProc::parseVec2i(line);
				animations[v.X()-1].second = (v.Y()-1);//vector indexes start at 0 and file indexes start at 1
			}
		}
	}
	infile.close();
}


void AnimSheet::loadseq(const std::string& s)
{
	if (pass == -1) {pass = 0;}

	switch (pass)
	{
	case 0:
		{
			Load(s);
			pass++;
			break;
		}
	case 1:
		{
			setNumCells( StringProc::parseVec2i(s));
			pass++;
			break;
		}
	case 2:
		{
			adjust = StringProc::parseVec2i(s);
			pass++;
			break;
		}
	case 3:
		{
			anims = StringProc::parseInt(s);
			lengths = new int[anims];
			animations.reserve(anims);//cut away some of the overhead introduced by vector
			for(int i = 0; i < anims; i++)
			{
				std::pair<std::vector<Vec2i>, int> v;
				animations.push_back(v);
			}
			pass++;
			break;
		}
	default:
		{
			//starts happening when pass == 4;
			static bool isStart = true;
			static Vec2i startPos(0,0);
			if (isStart)
			{
				startPos = StringProc::parseVec2i(s);
			}
			else
			{
				int atAnim = ((pass-4)/2); //the current animation index
				Vec2i endPos = StringProc::parseVec2i(s);
				Vec2i current = startPos;
				lengths[atAnim] = (numCells.X() - startPos.X() + 1) + ((endPos.Y() - startPos.Y() - 1)*numCells.X()) + endPos.X();
				animations[atAnim].first.reserve(lengths[atAnim]);//again, cutting overhead forced upon the program by C++'s clumsy array management
				for (int i = 0; i < lengths[atAnim]; i++)
				{
					animations[atAnim].first.push_back(Vec2i(0,0));
				}
				for(int i = 0; i < lengths[atAnim]; i++)
				{
					animations[atAnim].first[i] = current;
					current = nextSprite(current);
				}
			}
			isStart = !isStart;
			pass++;
			break;
		}
	}
}


Vec2i AnimSheet::nextSprite(Vec2i current) const
{
	if (current.X() != numCells.X())
	{
		current.setX(current.X()+1);
	}
	else
	{
		current.setX(0);
		if ( current.Y() != numCells.Y())
		{
			current.setY(current.Y()+1);
		}
		else
		{
			current.setY(0);
		}
	}
	return current;
}

std::vector<std::pair<Vec2<Vec2i>,int> >  AnimSheet::getAnims() const
{
	std::vector<std::pair<Vec2<Vec2i>,int> > ret;
	for(unsigned int i = 0; i < animations.size(); i++)
	{
		Vec2<Vec2i> v(animations[i].first[0],animations[i].first[animations[i].first.size()-1]);
		std::pair<Vec2<Vec2i>,int> p(v,animations[i].second);
		ret.push_back(p);
	}
	return ret;
}

int AnimSheet::getCellIndex(const Vec2i &cell) const
{
	int i = 0;
	Vec2i tc(1,1);
	while (tc != cell)
	{
		tc = nextSprite(tc);
		i++;
	}
	return i;
}

