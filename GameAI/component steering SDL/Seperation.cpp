#include "Seperation.h"
#include "Unit.h"
#include "UnitManager.h"
#include "Game.h"
Seperation::Seperation(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	{
		mType = Steering::SEPERATION;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);


}

Vector2D Seperation::getSeperation()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	Vector2D tmp;
	map<UnitID, Unit*> mMap = gpGame->getUnitManager()->getMap();
	//new direction
	//flock count
	int threshold = 0;

	float x, y;
	map<UnitID, Unit*>::iterator unit;
	for (unit = mMap.begin(); unit != mMap.end(); unit++)
	{
		//check to make sure the unit isnt This unit
		if (unit->second != pOwner)
		{
			Vector2D myCurrentDirection = unit->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition();
			float distance = myCurrentDirection.getLength();
			//check if target is close and then try to get in radius of it
			if (distance < mRadius)
			{
				tmp += myCurrentDirection;
				//tmp = myFinalDirection.getX() + unit->second->getPhysicsComponent()->getVelocity().getX();
				//myFinalDirection.setX(tmp);
				//tmp = myFinalDirection.getY() + unit->second->getPhysicsComponent()->getVelocity().getY();
				//myFinalDirection.setY(tmp);
				threshold++;
			}

		}
	}

	if (threshold == 0)
	{
		return mFinalDirection;
	}

	//reverse the velocity and average out the positions
	tmp *= -1;
	mFinalDirection = tmp;

	return mFinalDirection;
}
