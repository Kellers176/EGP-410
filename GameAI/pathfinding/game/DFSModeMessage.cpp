#include "DFSModeMessage.h"

DFSModeMessage::DFSModeMessage()
	:GameMessage(DFS_MODE)
{
}

DFSModeMessage::~DFSModeMessage()
{
}

void DFSModeMessage::process()
{
	gpGame->setDoneLoop(false);
	gpGame->setPathType(0);
}
