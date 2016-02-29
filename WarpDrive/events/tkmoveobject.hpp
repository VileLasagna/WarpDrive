#ifndef TK_MOVE_OBJECT_H
#define TK_MOVE_OBJECT_H

#include "events/timelinekey.hpp"
#include "basemaths/vec3.hpp"
#include <string>

class TKMoveObject: public TimelineKey
{
public:

	TKMoveObject
		(float Time = -0.01 , //by default it comes right after the last added key
		std::string ObjName = "", //The name or Type of the object/objects you want to influence
		bool UniqueID = true, //if this is true you are referring to a single object, else you want to alter all objects of a specific type
		bool ChangePos = false, 
		bool ChangeVel = false, 
		bool ChangeAccel = false, 
		const Vec3f& Pos = Vec3f(0,0,0), 
		const Vec3f& Vel= Vec3f(0,0,0), 
		const Vec3f& Accel= Vec3f(0,0,0));
	void Trigger();

protected:

	Vec3f pos,vel,acc;
	Vec3<bool> changes;
	std::string Name;
	bool isUnique;


};

#endif //TK_MOVE_OBJECT_H
