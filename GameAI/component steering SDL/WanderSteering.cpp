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

Vector2D WanderSteering::to2DVector(float convert)
{
	Vector2D value;
	value.setX(cos(convert));
	value.setY(sin(convert));
	return value;
}

Steering * WanderSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData owner = pOwner->getPhysicsComponent()->getData();
	float wanderOffset = 100.0;
	float wanderRadius = 80.0;
	mWanderRate = 2.0 * 3.1415;
	mWanderOrientation = 0;

		//need to allow for negative orientation
		mWanderOrientation += genRandomBinomial() * mWanderRate;

		mTargetOrientation = mWanderOrientation + pOwner->getFacing();

		//character orientation
		Vector2D currentDirection = to2DVector(pOwner->getFacing());
		currentDirection.normalize();

		//target orientation
		Vector2D targetDirection = to2DVector(mTargetOrientation);

		mTargetLoc = pOwner->getPositionComponent()->getPosition() + currentDirection * wanderOffset;
		mTargetLoc += targetDirection * wanderRadius;
		mFaceSteering.setTargetLoc(mTargetLoc);

		PhysicsData data = pOwner->getPhysicsComponent()->getData();
		Steering* mSteer = mFaceSteering.getSteering();

		if (mSteer != NULL)
		{
			data.rotAcc = mSteer->getData().rotAcc;
		}
		data.acc = currentDirection * MAX_ACC;

		this->mData = data;
		return this;
}
