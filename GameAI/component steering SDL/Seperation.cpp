#include "Seperation.h"
#include "Game.h"
#include "UnitManager.h"

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
	float tmp;
	map<UnitID, Unit*> mMap = gpGame->getUnitManager()->getMap();
	//new direction
	Vector2D myFinalDirection;
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
				tmp = myFinalDirection.getX() + (unit->second->getPositionComponent()->getPosition().getX() - pOwner->getPositionComponent()->getPosition().getX());
				myFinalDirection.setX(tmp);
				tmp = myFinalDirection.getY() + (unit->second->getPositionComponent()->getPosition().getY() - pOwner->getPositionComponent()->getPosition().getY());
				myFinalDirection.setY(tmp);
				threshold++;
			}

		}
	}

	if (threshold == 0)
	{
		return myFinalDirection;
	}

	//reverse the velocity and average out the positions
	tmp = myFinalDirection.getX() / threshold;
	tmp *= -1;
	myFinalDirection.setX(tmp);

	tmp = myFinalDirection.getX() / threshold;
	tmp *= -1;
	myFinalDirection.setY(tmp);

	myFinalDirection.normalize();

	return myFinalDirection;
}
