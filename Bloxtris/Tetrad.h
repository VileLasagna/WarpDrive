#ifndef TETRAD_H
#define TETRAD_H

#include "basesystem/GameObject.h"
#include "basemaths/Vec4.h"
#include "Brick.h"

class Tetrad: public GameObject
{

public:

    Tetrad();
    void Update();
    void Draw();
    const char* getType()const {return "Tetrad";}
    void nudge(int h, int v);
    void setPivot(Vec2i p) {pivot = p;}
    Vec2i getPivot() const {return pivot;}
    int getShape() const {return type;}
    void spin();
    Vec4<Vec2i> getBricks(); //returns the grid position of each brick


private:

    Vec2i pivot; //the grid position of the tetrad pivot
    int orient;
    int type; //0 = cube, 1 = T, 2 = I, 3 = L, 4 = ? 5 = S, 6 = Z
    static Brick* getModel(int color);

};

#endif //TETRAD_H
