#pragma once

#include "GameMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "Dijkstra.h"

class DijkstraModeMessage : public GameMessage
{
public:
	DijkstraModeMessage();
	~DijkstraModeMessage();

	void process();
private:
};