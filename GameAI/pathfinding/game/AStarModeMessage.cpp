#include "AStarModeMessage.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

AStarModeMessage::AStarModeMessage()
	:GameMessage(ASTAR_MODE)
{
}

AStarModeMessage::~AStarModeMessage()
{
}

void AStarModeMessage::process()
{
	gpGame->setDoneLoop(false);
	gpGame->setPathType(2);
}
