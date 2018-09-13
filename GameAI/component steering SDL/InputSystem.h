#pragma once

#include "Trackable.h"
#include "SDL.h"
#include "Event.h"

class InputSystem : public Trackable
{
public:
	InputSystem();
	~InputSystem();

	void init();
	void cleanup();

	void updateInputSystem(double dt);

	void updateKeyboard();


private:
	Event mSystemEvent;
	SDL_Event mEvent;

};