#pragma once
#include "Trackable.h"
#include "SDL.h"
#include "GameMessageManager.h"
#include "Vector2D.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();
	void updateKeyboard();



private:
	SDL_Event mEvent;

	int mPosX, mPosY;

	GameMessageManager* mpMessageManager;
};