#pragma once
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
#include <Trackable.h>
#include "Steering.h"
class Cohesion : public Steering
{
public:
	Cohesion(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee);
	virtual Steering* getSteering();

private:
	const float mRadius = 75.0f;
};