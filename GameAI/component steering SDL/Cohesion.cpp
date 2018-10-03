#include "Cohesion.h"
#include "Unit.h"
#include "UnitManager.h"
#include "Game.h"

Cohesion::Cohesion(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::COHESION;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Vector2D Cohesion::getCohesion()
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
				tmp = myFinalDirection.getX() + unit->second->getPositionComponent()->getPosition().getX();
				myFinalDirection.setX(tmp);
				tmp = myFinalDirection.getY() + unit->second->getPositionComponent()->getPosition().getY();
				myFinalDirection.setY(tmp);
				threshold++;
			}
			
		}
	}

	if (threshold == 0)
	{
		return myFinalDirection;
	}

	//average out locations
	//average out locations
	tmp = myFinalDirection.getX() / threshold;
	myFinalDirection.setX(tmp);

	tmp = myFinalDirection.getY() / threshold;
	myFinalDirection.setY(tmp);

	myFinalDirection = Vector2D(myFinalDirection.getX() - pOwner->getPositionComponent()->getPosition().getX(), 
		myFinalDirection.getY() - pOwner->getPositionComponent()->getPosition().getY());
	myFinalDirection.normalize();

	return myFinalDirection;
}
