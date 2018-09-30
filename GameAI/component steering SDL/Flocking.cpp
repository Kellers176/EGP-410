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
	mWander(WanderSteering(ownerID, targetLoc, mTargetID, false))
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
	Steering* mTempCohesion = mCohesion.getSteering();
	Steering* mTempAlign = mAlignment.getSteering();
	Steering* mTempSeperate = mSeperation.getSteering();
	Steering* mTempWander = mWander.getSteering();


	data.acc.setX((mData.acc.getX() + (mTempAlign->getData().acc.getX() * mGroupAlignmentWeight) + (mTempCohesion->getData().acc.getX() * mCohesionWeight) + (mTempSeperate->getData().acc.getX() * mSeperationWeight)));
	data.acc.setY((mData.acc.getY() + (mTempAlign->getData().acc.getY() * mGroupAlignmentWeight) + (mTempCohesion->getData().acc.getY() * mCohesionWeight) + (mTempSeperate->getData().acc.getY() * mSeperationWeight)));
	
	data.acc.normalize();
	data.acc *= pOwner->getMaxAcc();

	updateBoidWeight();
	this->mData = data;
	return this;
}

void Flocking::updateBoidWeight()
{
	mGroupAlignmentWeight = gpGame->getAlignmentWeight();
	mCohesionWeight = gpGame->getCohesionWeight();
	mSeperationWeight = gpGame->getSeperationWeight();
}
