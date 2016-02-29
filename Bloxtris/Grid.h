#ifndef PLAY_GRID_H
#define PLAY_GRID_H

#include "basesystem/GameObject.h"
#include "Brick.h"
#include "Tetrad.h"
#include "Sound/SoundFX.h"
#include <Vector>

class Grid: public GameObject
{
public:

	Grid();
	void Update();
	void Draw();
	const char* getType() const {return "PlayGrid";}
	void setSize(int w = 10, int h = 15);
	Vec2i getSize() const {return Vec2i(W,H);}
	//the next 3 functions deal with the active piece falling in the field, if any.
	void spin();
	void drop();
	void nudge(bool left = true);
	bool GameOver();
	void Reset();
	
private:

	void lines();
	bool collision(); //checks if the current piece has settled
	std::vector<Brick*> GD;
	int W;
	int H;
	Tetrad* current;
	SoundFX* spinfx;
	SoundFX* dropfx;
	SoundFX* linefx;
	SoundFX* failfx;
	int linecount;
	bool canNudge(bool left);




};

#endif //PLAY_GRID_H
