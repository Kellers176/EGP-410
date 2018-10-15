#include "AStar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

AStar::AStar(Graph * pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}

AStar::~AStar()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path * AStar::findPath(Node * pFrom, Node * pTo)
{
	return nullptr;
}
