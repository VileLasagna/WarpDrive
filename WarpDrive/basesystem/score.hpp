#ifndef WD_SCORE_HPP_DEFINED
#define WD_SCORE_HPP_DEFINED

#include "basesystem/gameobject.hpp"
#include "3dmaths/billboard.hpp"
#include "display/texture.hpp"
#include "display/sdlttf.hpp"
#include <set>

class Score:public GameObject
{
public:
	Score();
    void update() override;
    void draw()const override;
    const char* Type() const override {return "score";}
	void add(int points);
    //void load() override;
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

#endif //WD_SCORE_HPP_DEFINED
