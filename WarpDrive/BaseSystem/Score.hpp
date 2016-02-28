#ifndef SCORE_H
#define SCORE_H

#include "BaseSystem/GameObject.hpp"
#include "3DMaths/Billboard.hpp"
#include "Display/Texture.hpp"
#include "Display/SDLTTF.hpp"
#include <set>

class Score:public GameObject
{
public:
	Score();
	void Update();
	void Draw();
	const char* getType() const {return "score";}
	void add(int points);
	void load();
	void save();
	void Reset();

private:

	int current;
	std::set<int> TopTen;
	float time;
	Billboard quad;
	SDLTTF* font;
	Texture* display;
};







#endif //SCORE_H
