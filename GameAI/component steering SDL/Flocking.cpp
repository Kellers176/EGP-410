#include "Flocking.h"
#include "Unit.h"
#include "UnitManager.h"
#include "Game.h"
Flocking::Flocking(const UnitID & ownerID, const Vector2D & targetLoc, const UnitID & targetID, bool shouldFlee)
	:Steering(),
	mCohesion(Cohesion(ownerID, targetLoc, mTargetID, false)),
	mAlignment(GroupAlignment(ownerID, targetLoc, mTargetID, false)),
	mSeperation(Seperation(ownerID, targetLoc, mTargetID, false))
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
	Steering* mTempCohesion = mCohesion.getSteering();
	Steering* mTempAlign = mAlignment.getSteering();
	Steering* mTempSeperate = mSeperation.getSteering();

	//PhysicsData tempCohesion = mCohesion->getSteering()->getData();
	//PhysicsData tempAlign = mAlignment->getSteering()->getData();
	//PhysicsData tempSeperate = mSeperation->getSteering()->getData();

	mData.acc.setX((mData.acc.getX() + (mTempAlign->getData().acc.getX() * mGroupAlignmentWeight) + (mTempCohesion->getData().acc.getX() * mCohesionWeight) + (mTempSeperate->getData().acc.getX() * mSeperationWeight)));
	mData.acc.setY((mData.acc.getY() + (mTempAlign->getData().acc.getY() * mGroupAlignmentWeight) + (mTempCohesion->getData().acc.getY() * mCohesionWeight) + (mTempSeperate->getData().acc.getY() * mSeperationWeight)));
	
	mData.acc.normalize();
	mData.acc *= pOwner->getMaxAcc();

	return this;
}

void Flocking::updateBoidWeight()
{
	mGroupAlignmentWeight = gpGame->getAlignmentWeight();
	mCohesionWeight = gpGame->getCohesionWeight();
	mSeperationWeight = gpGame->getSeperationWeight();
}
