#pragma once

#include "GameMessage.h"
#include "Game.h"
#include "AStar.h"
#include "GameApp.h"
#include "GridPathfinder.h"

class AStarModeMessage : public GameMessage
{
public:
	AStarModeMessage();
	~AStarModeMessage();

	void process();
private:
};