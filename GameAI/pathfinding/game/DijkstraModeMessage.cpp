#include "DijkstraModeMessage.h"

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
