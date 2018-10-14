#pragma once

#include "GameMessage.h"
#include "Game.h"

class ExitMessage : public GameMessage
{
public:
	ExitMessage();
	~ExitMessage();

	void process();
private:
};