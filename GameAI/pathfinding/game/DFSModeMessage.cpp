#include "DFSModeMessage.h"
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

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
