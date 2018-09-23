#include <cassert>
#include "ArriveSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

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
	float targetRadius = 10.0;
	float slowRadius = 200.0;
	float timeToTarget = 0.1;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
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
		return NULL;
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


	//target velocity combines speed and direction
	targetVelocity = direction;
	targetVelocity.normalize();
	targetVelocity *= targetSpeed;

	data.acc = targetVelocity - data.vel;
	data.acc /= timeToTarget;

	if (targetVelocity.getLength() > MAX_ACC)
	{
		data.acc.normalize();
		data.acc *= MAX_ACC;
	}

	data.rotVel = 0;
	this->mData = data;
	return this;
}
