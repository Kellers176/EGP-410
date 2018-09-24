#include <cassert>
#include "FaceSteering.h"
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


FaceSteering::FaceSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	: Steering()
{

	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::FACE;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

float FaceSteering::MapToRange(float rotation)
{
	float convertRot;

	convertRot = fmod((rotation), 2.0 * 3.1415);
	if (convertRot > 3.1415)
	{
		convertRot -= 2.0 * 3.1415;
	}
	else if (convertRot < -3.1415)
	{
		convertRot += 2.0 * 3.1415;
	}
	return convertRot;
}

Steering * FaceSteering::getSteering()
{
	Vector2D direction;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	float myAngle ;
	float rotationSize;
	float targetRotation;

	if (mType == Steering::FACE)
	{
		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		direction = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}

	myAngle = atan2(direction.getY(), direction.getX()) - pOwner->getFacing();

	MapToRange(myAngle);

	rotationSize = abs(myAngle);


	
	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//check if they are there
	if (rotationSize < mTargetRadius)
	{
		data.rotAcc = 0;
		data.rotVel = 0;
		this->mData = data;
		return this;
	}

	if (rotationSize > mSlowRadius)
	{
		targetRotation = pOwner->getMaxRotVel();
	}
	else
	{
		targetRotation = pOwner->getMaxRotVel() * rotationSize / mSlowRadius;
	}

	targetRotation *= myAngle / rotationSize;

	//steering.angular
	data.rotAcc = targetRotation - data.rotVel; //<- character.rotation
	data.rotAcc /= mTimeToTarget;

	float angularAcceleration = abs(data.rotAcc);

	if (angularAcceleration > pOwner->getMaxRotAcc())
	{
		data.rotAcc /= angularAcceleration;
		data.rotAcc *= pOwner->getMaxRotAcc();
	}
	//steering.linear
	data.vel = 0;
	this->mData = data;
	return this;
}
