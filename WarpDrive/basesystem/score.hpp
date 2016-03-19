#ifndef SCORE_H
#define SCORE_H

#include "basesystem/gameobject.hpp"
#include "3dmaths/billboard.hpp"
#include "display/texture.hpp"
#include "display/sdlttf.hpp"
#include <set>

class Score:public GameObject
{
public:
	Score();
    void Update() override;
    void Draw()const override;
    const char* getType() const override {return "score";}
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
