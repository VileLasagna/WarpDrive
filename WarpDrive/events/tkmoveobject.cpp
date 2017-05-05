#include "WarpDrive/events/tkmoveobject.hpp"
#include "WarpDrive/basesystem/game.hpp"


TKMoveObject::TKMoveObject(float Time, std::string ObjName, bool UniqueID, bool ChangePos, bool ChangeVel, bool ChangeAccel, const Vec3f &Pos, const Vec3f &Vel, const Vec3f &Accel)
{
	isUnique = UniqueID;
	time = Time;
	changes = Vec3<bool>(ChangePos,ChangeVel,ChangeAccel);
	pos = Pos;
	vel = Vel;
	acc = Accel;
	name = ObjName;

}

void TKMoveObject::trigger()
{

	if(!isUnique)
	{
		Game::iterator it(name);
		if (it.isEmpty())
		{
			Err::Notify("TKMoveObject couldn't find objects of type: "+name);
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
			while ( it.next());
		}
	}
	else
	{
		Game::iterator it;
		if(!(it.seekName(name)))
		{
			Err::Notify("TKMoveObject couldn't find specific Object: "+name);
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
