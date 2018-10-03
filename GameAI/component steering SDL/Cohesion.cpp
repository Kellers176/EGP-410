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

Steering * Cohesion::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	map<UnitID, Unit*> mMap = gpGame->getUnitManager()->getMap();
	//new direction
	Vector2D direction = (0, 0);
	//flock count
	int threshold = 0;

	float x, y;

	map<UnitID, Unit*>::iterator unit;
	for (unit = mMap.begin(); unit != mMap.end(); unit++)
	{
		//check to make sure the unit isnt This unit
		if (unit->second != pOwner)
		{
			x = (unit->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getX();
			y = (unit->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getY();

			//check if target is close and then align
			if ((unit->second->getPositionComponent()->getPosition().getX() - pOwner->getPositionComponent()->getPosition().getX()) < mRadius
				&& (unit->second->getPositionComponent()->getPosition().getY() - pOwner->getPositionComponent()->getPosition().getY()) < mRadius)
			{
					direction.setX(direction.getX() + unit->second->getPositionComponent()->getPosition().getX());
					direction.setY(direction.getY() + unit->second->getPositionComponent()->getPosition().getY());

					threshold++;
				
			}
		}
	}

	if (threshold == 0)
	{
		this->mData.acc = direction;
		return this;
	}

	//get average calculations of each unit
	direction.setX(direction.getX() / threshold);
	direction.setY(direction.getY() / threshold);

	direction.setX(direction.getX() - pOwner->getPositionComponent()->getPosition().getX());
	direction.setY(direction.getY() - pOwner->getPositionComponent()->getPosition().getY());
	
	direction.normalize();

	this->mData.acc = direction;
	return this;
}
