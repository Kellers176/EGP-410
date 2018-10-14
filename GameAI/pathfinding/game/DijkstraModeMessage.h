#pragma once

#include "GameMessage.h"
#include "Game.h"

class DijkstraModeMessage : public GameMessage
{
public:
	DijkstraModeMessage();
	~DijkstraModeMessage();

	void process();
private:
};