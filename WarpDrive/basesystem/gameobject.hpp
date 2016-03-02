
#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <vector>

#include "basesystem/filemanager.hpp"
#include "basesystem/managedfile.hpp"
#include "basesystem/displaymanager.hpp"
#include "basemaths/vec3.hpp"
#include "basemaths/sphere.hpp"
#include "physics/alignedboundingbox.hpp"
#include "events/objectevent.hpp"


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
    virtual void setName(std::string&& s) { name = s;}

    virtual void setType(const std::string& s) { type = s;}
    virtual void setType(std::string&& s) { type = s;} //for organizing groups of objects
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

    virtual AABBox getBox() const noexcept;
    virtual Sphere getSphere() const noexcept;

    virtual Vec3f getVel() const noexcept {return vel;}
    virtual Vec3f getPos() const noexcept {return pos;}
    virtual Vec3f getAcc() const noexcept {return accel;}
    virtual Vec3f Dimensions() const noexcept {return dimensions;}
    virtual float Radius() const noexcept {return radius;}
    virtual std::string getName() const noexcept {return name;}
	bool isDead() {return removeMe;}
	void KILL() {removeMe = true;}


protected:

	Vec3f vel;
	Vec3f pos;
	Vec3f accel;
    float radius;
    Vec3f dimensions;
	std::string name;
	std::string type;
	std::vector<GOEvent*> events;
	bool removeMe;

};


#endif //GAME_OBJECT_H
