#pragma once

#include "GameMessage.h"
#include "Game.h"

class AStarModeMessage : public GameMessage
{
public:
	AStarModeMessage();
	~AStarModeMessage();

	void process();
private:
};