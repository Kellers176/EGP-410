#include <cassert>

#include "FaceSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <math.h>


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
		convertRot = (convertRot - 3.1415) * -1.0;
	}
	else if (convertRot < -3.1415)
	{
		convertRot = (convertRot * 3.1415) * -1.0;
	}
	return convertRot;
}

Steering * FaceSteering::getSteering()
{
	Vector2D direction;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);

	float targetRadius = 10.0 / 180.0 * 3.1415;
	float slowRadius = 250.0 / 180.0 * 3.1415;
	float myAngle ;
	float rotationSize;
	float targetRotation;
	float timeToTarget = 0.1;



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
	if (rotationSize < targetRadius)
	{
		return NULL;
	}

	if (rotationSize > slowRadius)
	{
		targetRotation = pOwner->getMaxRotVel();
	}
	else
	{
		targetRotation = pOwner->getMaxRotVel() * rotationSize / slowRadius;
	}

	targetRotation *= myAngle / rotationSize;

	//steering.angular
	data.rotAcc = targetRotation - data.rotVel; //<- character.rotation
	data.rotAcc /= timeToTarget;

	float angularAcceleration = abs(data.rotAcc);

	if (angularAcceleration > pOwner->getMaxRotAcc())
	{
		data.rotAcc /= angularAcceleration;
		data.rotAcc *= pOwner->getMaxRotAcc();
	}
	//steering.linear
	this->mData = data;
	return this;
}
