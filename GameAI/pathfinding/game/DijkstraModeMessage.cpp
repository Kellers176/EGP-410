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
	gpGame->setPathType(1);
}
