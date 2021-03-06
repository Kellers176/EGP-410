#pragma once
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
#include <Trackable.h>
#include "Steering.h"

class FaceSteering : public Steering
{
public:
	FaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);

	float MapToRange(float rotation);


	virtual Steering* getSteering();

private:
	const float mTargetRadius = 0.1f;
	const float mSlowRadius = 0.5f;
	const float mTimeToTarget = 0.1f;

	float myAngle;
	float rotationSize;
	float targetRotation;
};