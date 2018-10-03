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
class GroupAlignment : public Steering
{
public:
	GroupAlignment(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee);
	Vector2D getAlignment();

private:
	const float mRadius = 100.0f;
	FaceSteering mFace;
};