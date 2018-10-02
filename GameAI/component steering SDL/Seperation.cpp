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
				x = (gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getX();
				y = (gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition() - pOwner->getPositionComponent()->getPosition()).getY();

				//check if target is close and seperate if necessary
				if ((gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition().getX() - pOwner->getPositionComponent()->getPosition().getX()) < mRadius
					&& (gpGame->getUnitManager()->getUnit(i)->getPositionComponent()->getPosition().getY() - pOwner->getPositionComponent()->getPosition().getY()) < mRadius)
				{
					direction.setX(direction.getX() + (x));
					direction.setY(direction.getY() + (y));

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

	//get average of the unit locations adn then reverse
	direction.setX((direction.getX() / threshold) * -1);
	direction.setY((direction.getY() / threshold) * -1);

	direction.normalize();

	this->mData.acc = direction;
	return this;

}
