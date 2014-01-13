#include "TKGridCommand.h"

TKGridCommand::TKGridCommand(float Time, Grid *G, int command)
{
	time = Time;
	GD = G;
	c = command;
}

void TKGridCommand::Trigger()
{
	if (!GD)
	{
		return;
	}
	else
	{
		switch (c)
		{
		case 0: GD->nudge(true);break;
		case 1: GD->nudge(false);break;
		case 2: GD->spin();break;
		case 3: GD->drop();break;
		default: assert(0);break;
		}
	}
}