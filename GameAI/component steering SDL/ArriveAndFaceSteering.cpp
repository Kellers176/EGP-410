#include "ArriveAndFaceSteering.h"
#include "Steering.h"
#include "Game.h"
#include "UnitManager.h"
#include "Unit.h"
#include <cassert>
ArriveAndFaceSteering::ArriveAndFaceSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::ARRIVE_AND_FACE;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}
float ArriveAndFaceSteering::MapToRange(float rotation)
{
	const float pie = 3.1415;
	if (rotation > pie)
	{
		rotation -= (2 * pie);
	}
	else if (rotation < -pie)
	{
		rotation += (2 * pie);
	}
	return rotation;
}
Steering * ArriveAndFaceSteering::getSteering()
{
	Vector2D direction;
	Vector2D targetVelocity;
	float distance;
	float targetSpeed;
	//float targetRadius = 5.0;
	//float slowRadius = 3.0;
	float timeToTarget = 0.1;
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	float targetRadius = 1.0 / 180.0 * 3.1415;
	float slowRadius = 200.0 / 180.0 * 3.1415;
	float myAngle;
	float rotationSize;
	float targetRotation;
	bool canArrive = false;

	direction = mTargetLoc - pOwner->getPositionComponent()->getPosition();
	distance = direction.getLength();
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	//face
	myAngle = atan2(direction.getY(), direction.getX()) - pOwner->getFacing() + (90.0 / 180.0 * 3.1415);

	MapToRange(myAngle);

	rotationSize = abs(myAngle);

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
	if (data.rotAcc >= targetRotation)
	{
		canArrive = true;
	}

	//if (canArrive)
	//{
		////arrive
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
		data.vel = direction;
	//}
	
	//data.rotVel = 0.0f;
	this->mData = data;
	//canArrive = false;
	return this;
}
