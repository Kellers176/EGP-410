#include <cassert>
#include "WanderSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <math.h>
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

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
	Vector2D temp;
	temp.setX(cos(convert));
	temp.setY(sin(convert));
	return temp;
}

Steering * WanderSteering::getSteering()
{
	Vector2D diff;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData owner = pOwner->getPhysicsComponent()->getData();
	float wanderOffset = 10.0;
	float wanderRadius = 80.0;
	mWanderRate = 2.0 * 3.1415;
	mWanderOrientation = 0;

		//need to allow for negative orientation
		mWanderOrientation += genRandomBinomial() * mWanderRate;

		mTargetOrientation = mWanderOrientation + (pOwner->getFacing() - 3.1415 / 2);

		//character orientation
		Vector2D currentDirection = to2DVector(pOwner->getFacing() - (3.12149 / 2)) * wanderOffset;

		Vector2D mytarget;

		//target orientation
		Vector2D targetDirection = to2DVector(mTargetOrientation);

		mTargetLoc = pOwner->getPositionComponent()->getPosition() + currentDirection * wanderOffset;
		mTargetLoc += targetDirection * wanderRadius;
		PhysicsData data = pOwner->getPhysicsComponent()->getData();
		mFaceSteering.setTargetLoc(mTargetLoc);

		Steering* mSteer = mFaceSteering.getSteering();

		if (mSteer != NULL)
		{
			data.rotAcc = mSteer->getData().rotAcc;
			data.rotVel = mSteer->getData().rotVel;
		}
		data.acc = currentDirection * pOwner->getMaxAcc();

		this->mData = data;
		return this;
}
