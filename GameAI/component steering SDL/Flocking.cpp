#include "Flocking.h"
#include "Unit.h"
#include "UnitManager.h"
#include "Game.h"
#include "WanderSteering.h"
Flocking::Flocking(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	:Steering(),
	mCohesion(Cohesion(ownerID, targetLoc, mTargetID, false)),
	mAlignment(GroupAlignment(ownerID, targetLoc, mTargetID, false)),
	mSeperation(Seperation(ownerID, targetLoc, mTargetID, false)),
	mWander(WanderSteering(ownerID, targetLoc, mTargetID, false)),
	mFace(FaceSteering(ownerID, targetLoc, mTargetID, false))
{
	if (shouldFlee)
	{
		mType = Steering::FLEE;
	}
	else
	{
		mType = Steering::FLOCK;
	}
	setOwnerID(ownerID);
	setTargetID(targetID);
	setTargetLoc(targetLoc);

	updateBoidWeight();
}


Steering * Flocking::getSteering()
{
	Unit* pOwner = gpGame->getUnitManager()->getUnit(mOwnerID);
	PhysicsData data = pOwner->getPhysicsComponent()->getData();
	Vector2D mTempCohesion = mCohesion.getCohesion();
	Vector2D mTempAlign = mAlignment.getAlignment();
	Vector2D mTempSeperate = mSeperation.getSeperation();
	Steering* mTempWander = mWander.getSteering();

	float x, y;

	data = mTempWander->getData();

	updateBoidWeight();
	x = data.acc.getX() + (mTempAlign.getX() * mGroupAlignmentWeight) + (mTempCohesion.getX() * mCohesionWeight) + (mTempSeperate.getX() * mSeperationWeight);
	y = data.acc.getY() + (mTempAlign.getY() * mGroupAlignmentWeight) + (mTempCohesion.getY() * mCohesionWeight) + (mTempSeperate.getY() * mSeperationWeight);
	
	Vector2D acc = Vector2D(x, y);
	
	data.acc = acc;

	this->mData = data;
	return this;
}

void Flocking::updateBoidWeight()
{
	mGroupAlignmentWeight = gpGame->getAlignmentWeight();
	mCohesionWeight = gpGame->getCohesionWeight();
	mSeperationWeight = gpGame->getSeperationWeight();
	mWanderWeight = gpGame->getWanderWeight();
}
