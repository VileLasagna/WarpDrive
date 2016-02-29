#include "events/tkmoveobject.hpp"
#include "basesystem/game.hpp"


TKMoveObject::TKMoveObject(float Time, std::string ObjName, bool UniqueID, bool ChangePos, bool ChangeVel, bool ChangeAccel, const Vec3f &Pos, const Vec3f &Vel, const Vec3f &Accel)
{
	isUnique = UniqueID;
	time = Time;
	changes = Vec3<bool>(ChangePos,ChangeVel,ChangeAccel);
	pos = Pos;
	vel = Vel;
	acc = Accel;
	Name = ObjName;

}

void TKMoveObject::Trigger()
{

	if(!isUnique)
	{
		Game::iterator it(Name);
		if (it.isEmpty())
		{
			Err::Notify("TKMoveObject couldn't find objects of type: "+Name);
		}
		else
		{
			do
			{
				if(changes.X())
				{
					it->setPos(pos);
				}
				if(changes.Y())
				{
					it->setVel(vel);
				}
				if(changes.Z())
				{
					it->setAcc(acc);
				}
			}
			while ( it.Next());
		}
	}
	else
	{
		Game::iterator it;
		if(!(it.seekName(Name)))
		{
			Err::Notify("TKMoveObject couldn't find specific Object: "+Name);
		}
		else
		{
			if(changes.X())
			{
				it->setPos(pos);
			}
			if(changes.Y())
			{
				it->setVel(vel);
			}
			if(changes.Z())
			{
				it->setAcc(acc);
			}
		}
	}
}
