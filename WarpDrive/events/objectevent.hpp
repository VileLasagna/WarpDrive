#ifndef WD_GAME_OBJECT_EVENT_HPP_DEFINED
#define WD_GAME_OBJECT_EVENT_HPP_DEFINED

class GameObject;

class GOEvent
{
    //class to define events or conditions that can be attached to and removed from gameObjects
public:

    GOEvent(){finished = false;}
    virtual ~GOEvent();
    bool Finished() {return finished;}
    virtual void update(GameObject* target) = 0;

protected:

    bool finished;
};

#endif //WD_GAME_OBJECT_EVENT_HPP_DEFINED
