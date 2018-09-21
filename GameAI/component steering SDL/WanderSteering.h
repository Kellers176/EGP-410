#pragma once
#include <Trackable.h>
#include "Steering.h"
#include "FaceSteering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

protected:
	virtual Steering* getSteering();

	FaceSteering mFaceSteering;

	float mWanderRate;
	float mTargetOrientation;
	float mWanderOrientation;
	
};