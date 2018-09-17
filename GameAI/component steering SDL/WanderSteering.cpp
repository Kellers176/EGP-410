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
	float wanderOffset = 10.0;
	float wanderRadius = 50.0;
	float wanderRate = 20 /180 *3.1415;

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
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	float wanderOrientation = data.maxRotAcc;
	wanderOrientation += genRandomBinomial() * wanderRate;

	float targetOrientation = wanderOrientation + pOwner->getPositionComponent()->getFacing();

	Vector2D currentDirection = Vector2D(cos(pOwner->getFacing()), sin(pOwner->getFacing()));

	Vector2D targetDirection = Vector2D(cos(targetOrientation), sin(targetOrientation));

	mTargetLoc = pOwner->getPositionComponent()->getPosition() + currentDirection * wanderOffset;
	mTargetLoc += targetDirection * wanderRadius;

	data.acc = currentDirection * MAX_ACC;
	
	this->mData = data;
	return this;
}
