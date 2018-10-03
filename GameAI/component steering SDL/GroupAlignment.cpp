#include "GroupAlignment.h"
#include "Unit.h"
#include "UnitManager.h"
#include "Game.h"

GroupAlignment::GroupAlignment(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::GROUP_ALIGNMENT;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering * GroupAlignment::getSteering()
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
		if(unit->second != pOwner)
		{
			x = (unit->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getX();
			y = (unit->second->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getY();

			//check if target is close and then align
			if ((unit->second->getPositionComponent()->getPosition().getX() - pOwner->getPositionComponent()->getPosition().getX()) < mRadius
				&& (unit->second->getPositionComponent()->getPosition().getY() - pOwner->getPositionComponent()->getPosition().getY()) < mRadius)
			{
				direction.setX(direction.getX() + unit->second->getPhysicsComponent()->getVelocity().getX());
				direction.setY(direction.getY() + unit->second->getPhysicsComponent()->getVelocity().getY());

				threshold++;
			}
			
		}
	}

	if (threshold == 0)
	{
		this->mData.acc = direction;
		return this;
	}

	//get average align of all unit
	direction.setX(direction.getX() / threshold);
	direction.setY(direction.getY() / threshold);

	direction.normalize();

	this->mData.acc = direction;
	return this;
}
