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
				temp.setX(temp.getX() + gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition().getX());
				temp.setY(temp.getY() + gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition().getY());

				threshold++;
			}
		}
	}

	if (threshold == 0)
	{
		this->mData.acc = temp;
		return this;
	}

	//calculate strength and move object
	temp.setX(temp.getX() / threshold);
	temp.setY(temp.getY() / threshold);

	temp.setX(temp.getX() - pOwner->getPositionComponent()->getPosition().getX());
	temp.setY(temp.getY() - pOwner->getPositionComponent()->getPosition().getY());
	
	temp.normalize();

	this->mData.acc = temp;
	return this;
}
