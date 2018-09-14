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
	rotation = (int)rotation % 360;
	if (abs(rotation) > 180)
	{
		if (rotation < 0)
		{
			rotation += 360;
		}
		else
			rotation -= 360;
	}
	return rotation;
}

Steering * FaceSteering::getSteering()
{
	Vector2D diff;
	float rotation;
	float rotationDirection;
	float targetRotation;
	float targetRadius = 0.02;
	float slowRadius = 0.01;
	float maxRotation = 0.1;

	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	//are we seeking a location or a unit?

	if (mTargetID != INVALID_UNIT_ID)
	{
		//seeking unit
		Unit* pTarget = gpGame->getUnitManager()->getUnit(mTargetID);
		assert(pTarget != NULL);
		mTargetLoc = pTarget->getPositionComponent()->getPosition();
	}

	if (mType == Steering::FACE)
	{
		diff = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	}
	else
	{
		diff = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}

	////get the direction to the target
	//rotationDirection = atan2(diff.getY(), diff.getX()) + (3.1415 / 2);
	//rotation = rotationDirection - pOwner->getPositionComponent()->getFacing();
	//
	////map the result ot the (-pi, pi) interval
	//rotation = MapToRange(rotation);
	//float rotationSize = abs(rotation);


	//if (rotationSize < targetRadius)
	//{
	//	//do nothin
	//}
	////if we are outside the slowRadius, use the maximum rotation
	//if (rotationSize > slowRadius)
	//{
	//	targetRotation = maxRotation;
	//}
	////otherwiise calculate a scaled rotation
	//else
	//{
	//	targetRotation = maxRotation * rotationSize / slowRadius;
	//}

	////final target var combines speed (already in the variable) and direction
	//targetRotation *= rotation / rotationSize;

	////this is definitely wrong in some way but idk how.....
	//float steeringRotation = (targetRotation - pOwner->getPositionComponent()->getFacing());
	//pOwner->getPositionComponent()->setFacing(steeringRotation);

	//float angularAcceleration = abs(steeringRotation);
	//if (angularAcceleration > pOwner->getMaxAcc())
	//{
	//	steeringRotation /= angularAcceleration;
	//	steeringRotation *= pOwner->getMaxAcc();
	//	pOwner->getPositionComponent()->setFacing(steeringRotation);
	//}
	//
	diff.normalize();
	diff *= pOwner->getMaxAcc();


	float velocityDirection = atan2(diff.getY(), diff.getX()) + (3.1415 / 2);
	pOwner->getPositionComponent()->setFacing(velocityDirection);

	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	data.vel = diff;
	//data.rotVel = 1.0f;
	this->mData = data;
	return this;
}
