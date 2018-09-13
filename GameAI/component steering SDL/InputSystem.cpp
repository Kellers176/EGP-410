#include "InputSystem.h"
#include "EventSystem.h"


InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
}

void InputSystem::init()
{
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
			//if (mEvent.key.keysym.sym == SDLK_SPACE)
			//{
			//	mEventSystem->fireEvent(SpaceEvent());
			//}
		}
	}
}