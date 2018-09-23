#pragma once
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
#include <Trackable.h>
#include "Steering.h"
#include "FaceSteering.h"

class WanderSteering : public Steering
{
public:
	WanderSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	Vector2D to2DVector(float convert);
	virtual Steering* getSteering();

protected:

	FaceSteering mFaceSteering;

	float mWanderRate;
	float mTargetOrientation;
	float mWanderOrientation;
	
};