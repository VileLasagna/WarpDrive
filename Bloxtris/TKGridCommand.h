#ifndef TK_GRID_COMMAND_H
#define TK_GRID_COMMAND_H

#include "Events/TimelineKey.h"
#include "Grid.h"

class TKGridCommand: public TimelineKey
{
public:

    TKGridCommand( float Time = 0, Grid* G = 0, int command = 0); //0 = left, 1 = right, 2 = spin, 3 = drop
    void Trigger();

private:

    Grid* GD;
    int c;

};

#endif //TK_GRID_COMMAND_H
