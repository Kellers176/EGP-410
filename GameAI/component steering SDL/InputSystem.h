#pragma once

#include "Trackable.h"
#include "SDL.h"
#include "Event.h"
#include "Vector2D.h"

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
	

private:
	Event mSystemEvent;
	SDL_Event mEvent;
	
	int mPosX, mPosY;

};