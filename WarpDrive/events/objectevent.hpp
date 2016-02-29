#ifndef GAME_OBJECT_EVENT_H
#define GAME_OBJECT_EVENT_H

class GameObject;

class GOEvent
{
	//class to define events or conditions that can be attached to and removed from gameObjects
public:

	GOEvent(){finished = false;}
	virtual ~GOEvent(){}
	bool isFinished() {return finished;}
	virtual void Update(GameObject* target) = 0;
	
protected:

	bool finished;
};

#endif //GAME_OBJECT_EVENT_H