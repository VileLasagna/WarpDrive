#include "basesystem/score.hpp"
#include "basesystem/game.hpp"
#include "basesystem/displaymanager.hpp"
#include "basesystem/ttfmanager.hpp"
#include "basesystem/stringproc.hpp"


Score::Score()
{
	font = TTFManager::instance()->getFont("data/arial.ttf", 48);
	Reset();
}

void Score::update()
{
	time += DisplayManager::instance()->getDtSecs();
}

void Score::Reset()
{
	quad = Billboard(5,Vec3f(10,10,0));
    //load();
	time = 0;
	current = 0;
}

void Score::add(int points)
{
	current+=points;
    font->draw(StringProc::intToString(current),display);
}


void Score::draw() const
{
    display->useThisTexture();
    quad.draw();
    display->useNoTexture();
}

//void Score::load()
//{
//	return;
//	/*std::ifstream f;
//	f.open("data/score.dat",ios_base::in);
//	if(f.bad())
//	{
//		assert(0);
//	}
//	std::string s;
//	int i = 0;
//	int score;
//	while(true)
//	{
//		if (f.eof() || f.bad())
//		{
//			break;
//		}
//		getline(s,f);
//		score = StringProc::parseInt(s);
//		TopTen.insert(score);
//	}
//	f.close();*/
//}

void Score::save()
{
	return;
	//TopTen.insert(current);
	//while(TopTen.size > 10)
	//{
	//	TopTen.erase(TopTen.begin();//smaller value
	//}
	//std::ofstream file;
	//file.open("data/score.dat",ios_base::trunc);
	//for(std::set<int>::iterator it = TopTen.begin(); it != TopTen.end(); it++)
	//{
	//	std::string s = StringProc::intToString(*it);
	//	file.write(s.c_str(),s.length());
	//}
	//file.close();
}


		






