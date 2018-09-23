#pragma once
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
#include <Trackable.h>
#include "Steering.h"
#include "ArriveSteering.h"
#include "FaceSteering.h"
class ArriveAndFaceSteering : public Steering
{
public:
	ArriveAndFaceSteering(const UnitID& ownerID, const Vector2D& targetLoc, const UnitID& targetID = INVALID_UNIT_ID, bool shouldFlee = false);
	float MapToRange(float rotation);
protected:
	virtual Steering* getSteering();
	ArriveSteering mArriveSteering;
	FaceSteering mFaceSteering;
};