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
	Vector2D direction = (0, 0);
	//flock count
	int threshold = 0;

	float x, y;

	for (int i = 0; i < gpGame->getUnitManager()->getUnitCount(); i++)
	{
		//check to make sure the unit isnt This unit
		if (gpGame->getUnitManager()->getUnit(i) != pOwner)
		{
			if (pOwner != NULL && gpGame->getUnitManager()->getUnit(i) != NULL)
			{
				Unit* unit = gpGame->getUnitManager()->getUnit(i);
				int distanceX = unit->getPositionComponent()->getPosition().getX() - pOwner->getPositionComponent()->getPosition().getX();
				int distanceY = unit->getPositionComponent()->getPosition().getY() - pOwner->getPositionComponent()->getPosition().getY();

				//check if target is close and then try to get in radius of it
				if (distanceX < mRadius && distanceY < mRadius)
				{
					direction += unit->getPositionComponent()->getPosition();
					threshold++;
				}
			}
		}
	}

	if (threshold == 0)
	{
		this->mData.acc = direction;
		return this;
	}

	//average out locations
	direction /= threshold;
	direction -= pOwner->getPositionComponent()->getPosition();
	direction.normalize();

	this->mData.acc = direction;
	return this;
}
