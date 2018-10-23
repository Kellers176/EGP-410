#include "DijkstraModeMessage.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

DijkstraModeMessage::DijkstraModeMessage()
	:GameMessage(DIJKSTRA_MODE)
{
}

DijkstraModeMessage::~DijkstraModeMessage()
{
}

void DijkstraModeMessage::process()
{
	//SWITCH TO DIJKSTRA MODE
	gpGame->setDoneLoop(false);
	gpGame->setPathType(1);
}
