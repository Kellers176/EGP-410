#pragma once

#include "GameMessage.h"
#include "Game.h"
#include "GameApp.h"
#include "GridPathfinder.h"
#include "DepthFirstPathfinder.h"

class DFSModeMessage : public GameMessage
{
public:
	DFSModeMessage();
	~DFSModeMessage();

	void process();
private:
};