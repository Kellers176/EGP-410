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
Steering * ArriveAndFaceSteering::getSteering()
{
	return nullptr;
}
//
//Steering * ArriveAndFaceSteering::getSteering()
//{
//	/*mFaceSteering->getSteering();
//	mArriveSteering->getSteering();*/
//}
