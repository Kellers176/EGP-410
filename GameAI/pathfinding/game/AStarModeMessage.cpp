#include "AStarModeMessage.h"


AStarModeMessage::AStarModeMessage()
	:GameMessage(ASTAR_MODE)
{
}

AStarModeMessage::~AStarModeMessage()
{
}

void AStarModeMessage::process()
{
	gpGame->setPathType(2);
}
