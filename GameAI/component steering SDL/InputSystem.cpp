#include "InputSystem.h"
#include "EventSystem.h"
#include "EscapeEvent.h"
#include "MousePosition.h"
#include "DEvent.h"
#include "EnterEvent.h"


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
