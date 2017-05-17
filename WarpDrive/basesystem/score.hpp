#ifndef WD_SCORE_HPP_DEFINED
#define WD_SCORE_HPP_DEFINED

#include "WarpDrive/basesystem/gameobject.hpp"
#include "WarpDrive/3dmaths/billboard.hpp"
#include "WarpDrive/display/texture.hpp"
#include "WarpDrive/display/sdlttf.hpp"

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
    WDTexture* display;
};

#endif //WD_SCORE_HPP_DEFINED
