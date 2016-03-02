#ifndef COLLISIONSYSTEM_H
#define COLLISIONSYSTEM_H

#include <string>
#include <map>

#include "basesystem/game.hpp"
#include "basesystem/gameobject.hpp"


class CollisionPair
{
public:

	CollisionPair (std::string t1, std::string t2)
	{
		if (t1 < t2)
		{
			fst = t1;
			snd = t2;
		}
		else
		{
			fst = t2;
			snd = t1;
		}
	}
	const std::string& first() const {return fst;}
	const std::string& second() const {return snd;}

    bool operator< (const CollisionPair& comp) const
    {
        if (first() < comp.first())
        {
            return true;
        }
        if (first() > comp.first())
        {
            return false;
        }
        //if executions reaches here, this->first() == comp.first()
        if (second() < comp.second())
        {
            return true;
        }
        else
        {
            return false;
        }
    }



private:

	std::string fst, snd;
};

//bool operator< (const CollisionPair& ref, const CollisionPair& comp)
//{
//    if (ref.first() < comp.first())
//    {
//        return true;
//    }
//    if (ref.first() > comp.first())
//    {
//        return false;
//    }
//    //if executions reaches here, this->first() == comp.first()
//    if (ref.second() < comp.second())
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
//}

typedef void (*func)(GameObject*, GameObject*);

class CollisionSystem
{
public:

    virtual ~CollisionSystem() {}
	virtual void Update(Game::iterator it) = 0; //Just to not forget how to go around this
    void load(CollisionPair cp,func f)
	{
		handlers[cp] = f;
	}

    void load(std::string t1, std::string t2, func f)
    {
        load (CollisionPair(t1,t2),f);
    }

    protected:

		std::map<CollisionPair,func> handlers;

};

#endif //COLLISIONSYSTEM_H
