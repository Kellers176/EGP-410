#pragma once
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment2
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
#include "Trackable.h"
#include "SDL.h"
#include "Event.h"
#include "Vector2D.h"

enum Weights
{
	COHESION_WEIGHT,
	SEPERATION_WEIGHT,
	GROUP_ALIGN_WEIGHT,
	WANDER_WEIGHT
};


class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();

	void updateInputSystem(double dt);

	void updateKeyboard();

	Vector2D getMousePosition();
	
	Weights currentWeight;

private:
	Event mSystemEvent;
	SDL_Event mEvent;
	
	int mPosX, mPosY;

	const float mChangeWeight = 0.1f;

	float mGroupAlignTemp;
	float mSeperationTemp;
	float mCohesionTemp;
	float mWanderTemp;

};