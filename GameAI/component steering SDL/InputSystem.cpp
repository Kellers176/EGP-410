#include "InputSystem.h"
#include "EventSystem.h"
#include "EscapeEvent.h"
#include "MousePosition.h"
#include "DEvent.h"
#include "AEvent.h"
#include "EnterEvent.h"
#include "Save.h"
#include "Game.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment1
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::init()
{
	mGroupAlignTemp = gpGame->getAlignmentWeight();
	mCohesionTemp = gpGame->getCohesionWeight();
	mSeperationTemp = gpGame->getSeperationWeight();
	mWanderTemp = gpGame->getWanderWeight();
	currentWeight = GROUP_ALIGN_WEIGHT;
}

void InputSystem::cleanup()
{
}

void InputSystem::updateInputSystem(double dt)
{
	updateKeyboard();
}

void InputSystem::updateKeyboard()
{
	EventSystem *mEventSystem = EventSystem::getInstance();
	//create events and stuff
	while (SDL_PollEvent(&mEvent) != 0)
	{
		if (mEvent.type == SDL_KEYDOWN)
		{
			if (mEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				mEventSystem->fireEvent(EscapeEvent(true));
			}
			if (mEvent.key.keysym.sym == SDLK_RETURN)
			{
				mEventSystem->fireEvent(EnterEvent());
			}
			if (mEvent.key.keysym.sym == SDLK_d)
			{
				mEventSystem->fireEvent(DEvent());
			}
			if (mEvent.key.keysym.sym == SDLK_a)
			{
				mEventSystem->fireEvent(AEvent());
			}
			if (mEvent.key.keysym.sym == SDLK_s)
			{
				if (mGroupAlignTemp > 1.0f)
				{
					mGroupAlignTemp = 1.0f;
				}
				else if (mCohesionTemp > 1.0f)
				{
					mCohesionTemp = 1.0f;
				}
				else if (mSeperationTemp > 1.0f)
				{
					mSeperationTemp = 1.0f;
				}

				if (mGroupAlignTemp < 0.0f)
				{
					mGroupAlignTemp = 0.0f;
				}
				else if (mCohesionTemp  < 0.0f)
				{
					mCohesionTemp = 0.0f;
				}
				else if (mSeperationTemp  < 0.0f)
				{
					mSeperationTemp = 0.0f;
				}
				gpGame->setAlignmentWeight(mGroupAlignTemp);
				gpGame->setCohesionWeight(mCohesionTemp);
				gpGame->setSeperationWeight(mSeperationTemp);
				gpGame->setWanderWeight(mWanderTemp);

				mEventSystem->fireEvent(Save());
			}


			if (mEvent.key.keysym.sym == SDLK_1)
			{
				currentWeight = GROUP_ALIGN_WEIGHT;
			}
			if (mEvent.key.keysym.sym == SDLK_2)
			{
				currentWeight = COHESION_WEIGHT;
			}
			if (mEvent.key.keysym.sym == SDLK_3)
			{
				currentWeight = SEPERATION_WEIGHT;
			}


			if (mEvent.key.keysym.sym == SDLK_EQUALS)
			{
				if (currentWeight == GROUP_ALIGN_WEIGHT)
				{
					mGroupAlignTemp += mChangeWeight;
					gpGame->setAlignmentWeight(mGroupAlignTemp);
				}
				else if (currentWeight == COHESION_WEIGHT)
				{
					mCohesionTemp += mChangeWeight;
					gpGame->setCohesionWeight(mCohesionTemp);
				}
				else if (currentWeight == SEPERATION_WEIGHT)
				{
					mSeperationTemp += mChangeWeight;
					gpGame->setSeperationWeight(mSeperationTemp);
				}
				else if (currentWeight == WANDER_WEIGHT)
				{
					mWanderTemp += mChangeWeight;
				}
			}

			if (mEvent.key.keysym.sym == SDLK_MINUS)
			{
				if (currentWeight == GROUP_ALIGN_WEIGHT)
				{
					mGroupAlignTemp -= mChangeWeight;
				}
				else if (currentWeight == COHESION_WEIGHT)
				{
					mCohesionTemp -= mChangeWeight;
				}
				else if (currentWeight == SEPERATION_WEIGHT)
				{
					mSeperationTemp -= mChangeWeight;
				}
				else if (currentWeight == WANDER_WEIGHT)
				{
					mWanderTemp -= mChangeWeight;
				}
			}
		}
		if (SDL_GetMouseState(&mPosX, &mPosY) & SDL_BUTTON(SDL_BUTTON_LEFT))
		{
			mEventSystem->fireEvent(MousePosition(mPosX, mPosY));
		}
	}

}

Vector2D InputSystem::getMousePosition()
{
	return Vector2D(mPosX, mPosY);
}
