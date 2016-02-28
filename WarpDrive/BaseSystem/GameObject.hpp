
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "BaseSystem/FileManager.hpp"
#include "BaseSystem/ManagedFile.hpp"
#include "BaseMaths/Vec3.hpp"
#include "BaseSystem/DisplayManager.hpp"
#include "Events/ObjectEvent.hpp"
#include <vector>

class GameObject

{
public:

	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual ~GameObject() = default;
	virtual bool Load(ManagedFile* ) {return true;}
	virtual const char* getType() const {return type.c_str();}

	virtual void setVel(const Vec3f& v) { vel = v;}
	virtual void setPos(const Vec3f& p) { pos = p;}
	virtual void setAcc(const Vec3f& a) { accel = a;}
	virtual void setName(const std::string& s) { name = s;}
	virtual void setType(const std::string& s) { type = s;} //for organizing groups of objects
															//TODO: Should be separate from type and also indexed in Game::iterator
	virtual void addEvent(GOEvent* e) {events.push_back(e);}
	virtual void clearEvents()
	{
	   /*
		for (std::vector<GOEvent*>::iterator it = events.begin(); it != events.end(); it++)
		{
		  GOEvent* e = *it;
		  delete e;
		}
	   */
		events.clear();
	}

	virtual Vec3f getVel() const {return vel;}
	virtual Vec3f getPos() const {return pos;}
	virtual Vec3f getAcc() const {return accel;}
	virtual std::string getName() const {return name;}
	bool isDead() {return removeMe;}
	void KILL() {removeMe = true;}


protected:

	Vec3f vel;
	Vec3f pos;
	Vec3f accel;
	std::string name;
	std::string type;
	std::vector<GOEvent*> events;
	bool removeMe;

};


#endif //GAME_OBJECT_H
