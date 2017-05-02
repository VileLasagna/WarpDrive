#ifndef WD_GAME_OBJECT_HPP_DEFINED
#define WD_GAME_OBJECT_HPP_DEFINED

#include <vector>

#include "WarpDrive/basesystem/filemanager.hpp"
#include "WarpDrive/basesystem/managedfile.hpp"
#include "WarpDrive/basesystem/displaymanager.hpp"
#include "WarpDrive/basemaths/vec3.hpp"
#include "WarpDrive/basemaths/sphere.hpp"
#include "WarpDrive/physics/alignedboundingbox.hpp"
#include "WarpDrive/events/objectevent.hpp"

class GameObject
{

public:

    GameObject();

    virtual void update() = 0;
    virtual void draw() const = 0;
	virtual ~GameObject() = default;
    virtual bool load(ManagedFile* ) {return true;}
    virtual const char* Type() const {return type.c_str();}

    virtual void setVel (const Vec3f& v) { vel = v;}
    virtual void setPos (const Vec3f& p) { pos = p;}
    virtual void setAcc (const Vec3f& a) { accel = a;}
    virtual void setMass(const float m)  { mass = m;}

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

    virtual AABBox BoundingBox() const noexcept;
    virtual Sphere BoundingSphere() const noexcept;

    virtual Vec3f Velocity() const noexcept {return vel;}
    virtual Vec3f Position() const noexcept {return pos;}
    virtual Vec3f Accel() const noexcept {return accel;}
    virtual Vec3f Dimensions() const noexcept {return dimensions;}
    virtual float Radius() const noexcept {return radius;}
    virtual std::string Name() const noexcept {return name;}
    virtual float Mass() const noexcept {return mass;}
    size_t Index() const noexcept {return index;}
	bool isDead() {return removeMe;}
	void KILL() {removeMe = true;}

protected:

    size_t index;
	Vec3f vel;
	Vec3f pos;
	Vec3f accel;
    float mass;
    float radius;
    Vec3f dimensions;
	std::string name;
	std::string type;
	std::vector<GOEvent*> events;
	bool removeMe;

};

#endif //WD_GAME_OBJECT_HPP_DEFINED
