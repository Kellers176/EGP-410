#include "ExitMessage.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

ExitMessage::ExitMessage()
	:GameMessage(END_GAME)
{
}

ExitMessage::~ExitMessage()
{
}

void ExitMessage::process()
{
	gpGame->endGame();
}
