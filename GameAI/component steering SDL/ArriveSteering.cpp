#include <cassert>

#include "ArriveSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"

ArriveSteering::ArriveSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::ARRIVE;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

}

Steering * ArriveSteering::getSteering()
{
	Vector2D diff;
	float radius = 5.0;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if (mType == Steering::ARRIVE)
	{
		diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		diff = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}


	if (diff.getLength() < radius)
	{
		//do nothing
	}
	if (diff.getLength() > MAX_SPEED)
	{
		diff.normalize();
		diff *= pOwner->getMaxAcc();
	}

	//float velocityDirection = atan2(diff.getY(), diff.getX()) + (3.1415 / 2);
	//pOwner->getPositionComponent()->setFacing(velocityDirection);

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.vel = diff;
	//data.rotVel = 1.0f;
	this->mData = data;
	return this;
}
