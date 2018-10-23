#pragma once
#include "GameMessage.h"
#include "Game.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Purpose: I am using this class for the message system in order to change the modes*/

class ExitMessage : public GameMessage
{
public:
	ExitMessage();
	~ExitMessage();

	void process();
private:
};