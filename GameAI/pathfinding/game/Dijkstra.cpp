#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

Dijkstra::Dijkstra(Graph * pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif

}

Dijkstra::~Dijkstra()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
}

Path * Dijkstra::findPath(Node * pFrom, Node * pTo)
{
	return nullptr;


}
