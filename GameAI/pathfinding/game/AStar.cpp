#include "AStar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;


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

	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it

	cout << pFrom->getId() << endl;
	cout << pTo->getId() << endl;
	NodeRecord startRecord = NodeRecord();
	//initialize the record for the start node
	startRecord.mNode = pFrom;
	startRecord.mConnection = NULL;
	startRecord.mCostSoFar = 0;
	startRecord.mEstimatedTotalCost;// = heuristic.estimate(Start);
	//initialize the record for the end node

	//create Path

	//Initialize the open and closed lists
	//open list where mVisitedNodes is the closed list
	list<NodeRecord> mOpen;
	mOpen.push_front(startRecord);
	list<NodeRecord> mClosed;

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif














	return NULL;
}
