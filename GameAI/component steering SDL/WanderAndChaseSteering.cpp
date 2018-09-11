#include "WanderAndChaseSteering.h"

WanderAndChaseSteering::WanderAndChaseSteering(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	: Steering()
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::SEEK;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);
}

Steering * WanderAndChaseSteering::getSteering()
{
	return nullptr;
}
