#pragma once

#include "GameMessage.h"
#include "Game.h"

class DFSModeMessage : public GameMessage
{
public:
	DFSModeMessage();
	~DFSModeMessage();

	void process();
private:
};