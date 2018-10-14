#include "InputSystem.h"
#include "Game.h"
#include "PathToMessage.h"
#include "ExitMessage.h"
#include "DijkstraModeMessage.h"
#include "DFSModeMessage.h"
#include "AStarModeMessage.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment2
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

InputSystem::InputSystem()
{
}

InputSystem::~InputSystem()
{
	cleanup();
}

void InputSystem::init()
{
	mpMessageManager = new GameMessageManager();
}

void InputSystem::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

}


void InputSystem::updateKeyboard()
{
	SDL_PumpEvents();
	int x, y;
	SDL_GetMouseState(&x, &y);

	SDL_PumpEvents();

	if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		static Vector2D lastPos(0.0f, 0.0f);
		Vector2D pos(x, y);
		if (lastPos.getX() != pos.getX() || lastPos.getY() != pos.getY())
		{
			GameMessage* pMessage = new PathToMessage(lastPos, pos);
			mpMessageManager->addMessage(pMessage, 0);
			lastPos = pos;
		}
	}

	//get input - should be moved someplace better
	//all this should be moved to InputManager!!!
	{
		//get keyboard state
		const Uint8 *state = SDL_GetKeyboardState(NULL);

		//if escape key was down then exit the loop
		if (state[SDL_SCANCODE_ESCAPE])
		{
			std::cout << "ESCAPE MODE ACTIVATED" << std::endl;
			GameMessage* pMessage = new ExitMessage();
			mpMessageManager->addMessage(pMessage, 0);
		}

		if (state[SDL_SCANCODE_A])
		{
			std::cout << "ASTAR MODE ACTIVATED" << std::endl;
			GameMessage* pMessage = new AStarModeMessage();
			mpMessageManager->addMessage(pMessage, 0);
		}
		if (state[SDL_SCANCODE_D])
		{
			std::cout << "DIJKSTRA MODE ACTIVATED" << std::endl;
			GameMessage* pMessage = new DijkstraModeMessage();
			mpMessageManager->addMessage(pMessage, 0);
		}
		if (state[SDL_SCANCODE_F])
		{
			std::cout << "DFS MODE ACTIVATED" << std::endl;
			GameMessage* pMessage = new DFSModeMessage();
			mpMessageManager->addMessage(pMessage, 0);
		}
	}
	mpMessageManager->processMessagesForThisframe();

}


