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

	x = (mTempAlign.getX() * mGroupAlignmentWeight) + (mTempCohesion.getX() * mCohesionWeight) + (mTempSeperate.getX() * mSeperationWeight);
	y = (mTempAlign.getY() * mGroupAlignmentWeight) + (mTempCohesion.getY() * mCohesionWeight) + (mTempSeperate.getY() * mSeperationWeight);
	
	Vector2D blendedWeights = Vector2D(x, y);
	blendedWeights.normalize();

	Vector2D mapOrientation(cos(pOwner->getFacing() * mRadius), sin(pOwner->getFacing() * mRadius));
	mapOrientation.normalize();

	mDirection.setX(cos(mRotation * 3.14f / 180.0f) * mRadius);
	mDirection.setY(sin(mRotation * 3.14f / 180.0f) * mRadius);

	mTargetDirection = mDirection + (mapOrientation * mOffset);
	mTargetDirection.normalize();
	mTargetDirection += blendedWeights;

	FaceSteering mFace(mOwnerID, mTargetDirection + pOwner->getPositionComponent()->getPosition(), mTargetID, false);
	data = mFace.getSteering()->getData();

	mTargetDirection.normalize();
	data.acc = mTargetDirection * MAX_ACC;

	this->mData = data;
	return this;
}

void Flocking::updateBoidWeight()
{
	mGroupAlignmentWeight = gpGame->getAlignmentWeight();
	mCohesionWeight = gpGame->getCohesionWeight();
	mSeperationWeight = gpGame->getSeperationWeight();

	if (mGroupAlignmentWeight > 1.0f)
	{
		gpGame->setAlignmentWeight(1.0f);
		mGroupAlignmentWeight = 1.0f;
	}
	else if (mCohesionWeight > 1.0f)
	{
		gpGame->setCohesionWeight(1.0f);
		mCohesionWeight = 1.0f;
	}
	else if (mSeperationWeight > 1.0f)
	{
		gpGame->setSeperationWeight(1.0f);
		mSeperationWeight = 1.0f;
	}

	if (mGroupAlignmentWeight < 0.0f)
	{
		gpGame->setAlignmentWeight(0.0f);
		mGroupAlignmentWeight = 0.0f;
	}
	else if (mCohesionWeight  < 0.0f)
	{
		gpGame->setCohesionWeight(0.0f);
		mCohesionWeight = 0.0f;
	}
	else if (mSeperationWeight  < 0.0f)
	{
		gpGame->setSeperationWeight(0.0f);
		mSeperationWeight = 0.0f;
	}
}
