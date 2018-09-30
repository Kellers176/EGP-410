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

	//new direction
	Vector2D temp = (0, 0);
	//flock count
	int threshold = 0;

	float x, y;

	for (int i = 0; i < gpGame->getUnitManager()->getUnitCount(); i++)
	{
		//check to make sure the unit isnt This unit
		if (gpGame->getUnitManager()->getUnit(i) != pOwner)
		{
			//set x and y to distance between two game objects
			x = (gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getX();
			y = (gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getY();

			//check if target is too close
			if ((gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition().getX() - pOwner->getPositionComponent()->getPosition().getX()) < mRadius
				&& (gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition().getY() - pOwner->getPositionComponent()->getPosition().getY()) < mRadius)
			{
				temp.setX(temp.getX() + gpGame->getUnitManager()->getUnit(i)->getPhysicsComponent()->getVelocity().getX());
				temp.setY(temp.getY() + gpGame->getUnitManager()->getUnit(i)->getPhysicsComponent()->getVelocity().getY());

				threshold++;
			}
		}
	}

	if (threshold == 0)
	{
		this->mData.acc = temp;
		return this;
	}

	
	temp.setX(temp.getX() / threshold);
	temp.setY(temp.getY() / threshold);

	temp.normalize();

	this->mData.acc = temp;
	return this;
}
