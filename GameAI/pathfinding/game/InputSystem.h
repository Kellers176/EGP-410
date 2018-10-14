#pragma once
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment2
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/
#include "Trackable.h"
#include "SDL.h"
#include "GameMessageManager.h"
#include "Vector2D.h"



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