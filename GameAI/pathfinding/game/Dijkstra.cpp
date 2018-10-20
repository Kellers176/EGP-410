#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

Dijkstra::Dijkstra(Graph * pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
#ifdef VISUALIZE_PATH
	mpPath = NULL;
#endif
	mReturnPath = nullptr;

}

Dijkstra::~Dijkstra()
{
#ifdef VISUALIZE_PATH
	delete mpPath;
#endif
	if (mReturnPath != nullptr)
	{
		delete mReturnPath;
	}
}
//returns the reverse path
Path * Dijkstra::TakeItBackYall(Path * path)
{
	Path* tmpPath = new Path();

	for (int i = 0; i < path->getNumNodes(); i++)
	{
		Node* newestNode;
		int lastIndex;

		lastIndex = path->getNumNodes() - (i + 1);
		newestNode = path->peekNode(lastIndex);

		tmpPath->addNode(newestNode);
	}
	if (tmpPath->getNumNodes() > 0)
	{
		return tmpPath;
	}
	else
	{
		return NULL;
	}
}

Path * Dijkstra::findPath(Node * pFrom, Node * pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it

	//initialize the record for the start node
	NodeRecord startRecord = NodeRecord();
	startRecord.mNode = pFrom;
	startRecord.mConnection = NULL;
	startRecord.mCostSoFar = 0;
	//initialize the record for the end node
	NodeRecord endRecord;
	//create Path
	Path* pPath = new Path();

	//Initialize the open and closed lists
	//open list where mVisitedNodes is the closed list
	vector<Node*> mOpen;
	mOpen.push_back(startRecord.mNode);
	vector<Node*> mClosed;

#ifdef VISUALIZE_PATH
	delete mpPath;
	mVisitedNodes.clear();
	mOpen.clear();
	mClosed.clear();
	mVisitedNodes.push_back(pFrom);
#endif
	//get current node
	NodeRecord pCurrentNode = NodeRecord();
	
	bool toNodeAdded = false;

	//Iterate through processing each node
	while (/*pCurrentNode != pTo && */mOpen.size() > 0)
	{
		//get current node from front of list
		pCurrentNode.mNode = mOpen.front();
		//remove node from list
		//nodesToVisit.pop_front();
		//add Node to Path

		if (pCurrentNode.mNode == pTo)
		{
			break;
		}
		else
		{
			//get the Connections for the current node
			vector<Connection*> connections = mpGraph->getConnections(pCurrentNode.mNode->getId());

			//Loop through each connection in turn
			for (unsigned int i = 0; i < connections.size(); i++)
			{
				Connection* pConnection = connections[i];
				//get the cost estimate for the end node
				Node* pEndNode = connections[i]->getToNode();
				float endNodeCost = pCurrentNode.mCostSoFar + connections[i]->getCost();
				//skip if the node is closed
				if (find(mClosed.begin(), mClosed.end(), pEndNode) != mClosed.end())
				{
					continue;
				}
				//or if it is open, we have found a worse route
				else if (find(mOpen.begin(), mOpen.end(), pEndNode) != mOpen.end())
				{
					endRecord.mNode = pEndNode;
					if (endRecord.mCostSoFar <= endNodeCost)
					{
						continue;
					}
				}
				//otherwise we know we've got an unvisited node, so make a record for it
				else
				{
					endRecord.mCostSoFar = endNodeCost;
					endRecord.mNode = pEndNode;
				}
				//we are here if we need to updatethe cost and connection
				endRecord.mConnection = pConnection;
				endRecord.mCostSoFar = endNodeCost;
				//add it to the open list
				if (find(mOpen.begin(), mOpen.end(), pEndNode) != mOpen.end())
				{
					//We've finished looking at the connections for the current node, 
					//so add it to the closed list and remove it from the open list
					mOpen.push_back(endRecord.mNode);
				}
			}
			
		}
		//# We’ve finished looking at the connections for
		//the current node, so add it to the closed list
		//and remove it from the open list 
		for (int i = 0; i < mOpen.size(); i++)
		{
			if (mOpen[i] == pCurrentNode.mNode)
			{
				mOpen.erase(mOpen.begin() + i);
				mClosed.push_back(pCurrentNode.mNode);
				mVisitedNodes.push_back(pCurrentNode.mNode);
				break;

			}
		}
		//We are here if we've found either the goal, or
		//if we have no more nodes to search, find which
		if (pCurrentNode.mNode != pTo)
		{
			//Weve run out of nodes without finding the goal, so no solution
			return NULL;
		}
		else
		{

			if (mReturnPath != nullptr)
			{
				delete mReturnPath;
			}
			mReturnPath = new Path();
			//return the reverse path
			while (pCurrentNode.mNode != pFrom)
			{
				mReturnPath->addNode(pCurrentNode.mNode);
				pCurrentNode.mNode = pCurrentNode.mConnection->getFromNode();
			}
			pPath = TakeItBackYall(pPath);
#ifdef VISUALIZE_PATH
			mpPath = mReturnPath;
#endif
		}

	}
	
	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return mReturnPath;
	delete mReturnPath;
}
