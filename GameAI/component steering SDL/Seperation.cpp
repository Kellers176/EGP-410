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

Steering * Seperation::getSteering()
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

				//check if target is too close try to align to it
				if (distanceX < mRadius && distanceY < mRadius)
				{
					direction += unit->getPhysicsComponent()->getAcceleration() - pOwner->getPositionComponent()->getPosition();
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

	//reverse the steering
	direction *= -1;
	//average out remaining units
	direction /= threshold;
	direction.normalize();

	this->mData.acc = direction;
	return this;
}
