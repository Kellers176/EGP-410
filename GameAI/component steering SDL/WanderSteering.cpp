#include <cassert>

#include "WanderSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <math.h>

WanderSteering::WanderSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::WANDER;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering * WanderSteering::getSteering()
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

	if (mType == Steering::WANDER)
	{
		diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		diff = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}

	float rotation = genRandomBinomial() * MAX_ROT_VEL;
	pOwner->getPositionComponent()->setFacing(rotation);


	//diff.normalize();
	//diff *= pOwner->getMaxAcc();


	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.vel = MAX_SPEED * pOwner->getFacing();
	//data.rotVel = 1.0f;
	this->mData = data;
	return this;
}
