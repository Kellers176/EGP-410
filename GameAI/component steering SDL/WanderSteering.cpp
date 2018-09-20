#include <cassert>

#include "WanderSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <math.h>

WanderSteering::WanderSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	: Steering()
	, mFaceSteering(FaceSteering(ownerID, targetLoc, targetID, shouldFlee))
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
	float wanderOffset = 0.0;
	float wanderRadius = 200.0;
	float wanderRate = 500 / 180 * 3.1415;

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
	//need to allow for negative orientation
	wanderOrientation += genRandomBinomial() * wanderRate;

	float targetOrientation = wanderOrientation + pOwner->getPositionComponent()->getFacing();

	Vector2D currentDirection = Vector2D(cos(pOwner->getFacing()), sin(pOwner->getFacing())) - 90 / 180 * 3.1415;

	Vector2D targetDirection = Vector2D(cos(targetOrientation), sin(targetOrientation)) - 90 / 180 * 3.1415;

	mTargetLoc = pOwner->getPositionComponent()->getPosition() + currentDirection * wanderOffset;
	mTargetLoc += targetDirection * wanderRadius;

	//add faceing
	Steering* mySteering = mFaceSteering.getSteering();

	/*if (mySteering)
	{
		mData.rotAcc = mySteering->getData().rotAcc;
	}
*/

	data.acc = currentDirection * pOwner->getMaxAcc();
	
	this->mData = data;
	return this;
}
