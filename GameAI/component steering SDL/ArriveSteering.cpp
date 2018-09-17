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
	Vector2D direction;
	Vector2D targetVelocity;
	float distance;
	float targetSpeed;
	float targetRadius = 5.0;
	float slowRadius = 3.0;
	float timeToTarget = 2.0;
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
		direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
		distance = direction.getLength();
	}
	else
	{
		direction = pOwner->getPositionComponent()->getPosition() - mTargetLoc;
	}

	//check to see if we are there, no steering
	if (distance < targetRadius)
	{
		//do nothing
	}

	//if the outside the slow radius, go the max speed
	if (distance > slowRadius)
	{
		targetSpeed = MAX_SPEED;
	}
	//calculate a scaled speed
	else
	{
		targetSpeed = MAX_SPEED * distance / slowRadius;
	}

	PhysicsData data = pOwner->getPhysicsComponent()->getData();

	//target velocity combines speed and direction
	targetVelocity = direction;
	targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	data.acc = targetVelocity - pOwner->getPhysicsComponent()->getAcceleration();
	data.acc /= timeToTarget;

	if (targetVelocity.getLength() > MAX_ACC)
	{
		data.acc.normalize();
		data.acc *= MAX_ACC;
	}

	
	//float velocityDirection = atan2(diff.getY(), diff.getX()) + (3.1415 / 2);
	//pOwner->getPositionComponent()->setFacing(velocityDirection);

	data.vel = direction;
	data.rotVel = 0.0f;
	this->mData = data;
	return this;
}
