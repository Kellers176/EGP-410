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
					direction.setX(direction.getX() + (x));
					direction.setY(direction.getY() + (y));

					threshold++;
				
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
