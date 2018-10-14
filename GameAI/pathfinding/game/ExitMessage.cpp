#include "ExitMessage.h"

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
