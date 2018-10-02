#include "GroupAlignment.h"
#include "Unit.h"
#include "UnitManager.h"
#include "Game.h"

GroupAlignment::GroupAlignment(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	:Steering(),
	mFace(FaceSteering(ownerID, targetLoc, targetID, false))
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
	Steering* mTempFace = mFace.getSteering();
	//new direction
	Vector2D direction = (0, 0);
	//flock count
	int threshold = 0;


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

				//check if arget is close enough and try to align
				if (distanceX < mRadius && distanceY < mRadius)
				{
					direction += unit->getPhysicsComponent()->getAcceleration();
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

	//cout << direction.getX() << "," << direction.getY() << endl;
	mFace.setTargetLoc(direction);
	data.rotAcc = mFace.getData().rotAcc;

	//average out all alignments
	direction /= threshold;
	direction.normalize();

	this->mData.acc = direction;
	return this;
}
