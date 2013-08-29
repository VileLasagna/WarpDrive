#ifndef SCORE_H
#define SCORE_H

#include "GameObject.h"
#include "Billboard.h"
#include "Texture.h"
#include "SDLTTF.h"
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