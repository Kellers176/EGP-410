#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Game.h"
#include <PerformanceTracker.h>
#include <list>
#include <algorithm>
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

using namespace std;

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
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");
	//allocate nodes to visit list and place starting node in it

	//initialize the record for the start node
	NodeRecord startRecord = NodeRecord();
	startRecord.mNode = pFrom;
	startRecord.mConnection = NULL;
	startRecord.mCostSoFar = 0;

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

	Path* mReturnPath = new Path();
	//get current node
	NodeRecord pCurrentNode;
	bool toNodeAdded = false;

	//Iterate through processing each node
	while (mOpen.size() > 0)
	{
		//get current node from front of list
		pCurrentNode = mOpen.front();
		//remove node from list
		mOpen.pop_front();

		//check if we are already there
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
				//create endRecord for list and also get current connections
				bool isInClosed = false, isInOpen = false, check = false;
				Connection* pConnection = connections[i];
				NodeRecord endRecord;
				//get the cost estimate for the end node
				Node* pEndNode = connections[i]->getToNode();
				float endNodeCost = pCurrentNode.mCostSoFar + connections[i]->getCost();

				//check if node is in the open or closed list
				for (list<NodeRecord>::iterator iter = mClosed.begin(); iter != mClosed.end(); iter++)
				{
					if (iter->mNode == pEndNode)
					{
						isInClosed = true;
						break;
					}
				}
				list<NodeRecord>::iterator tmp;
				for (list<NodeRecord>::iterator iter = mOpen.begin(); iter != mOpen.end(); iter++)
				{
					if (iter->mNode == pEndNode)
					{
						tmp = iter;
						isInOpen = true;
						break;
					}
				}

				//Do calculations based on if inside different lists
				if (isInClosed)
				{
					continue;
				}
				else if (isInOpen)
				{
					pEndNode = tmp->mNode;
					if (endRecord.mCostSoFar <= endNodeCost)
					{
						continue;
					}
				}
				else
				{
					endRecord = NodeRecord(pEndNode, pConnection, endNodeCost);
				}
				//add it to the open list
				if (!isInOpen && !check)
				{
					//We've finished looking at the connections for the current node, 
					//so add it to the closed list and remove it from the open list
					mOpen.push_back(endRecord);
					if (endRecord.mNode == pTo)
					{
						check = true;
					}
#ifdef VISUALIZE_PATH
					mVisitedNodes.push_back(endRecord.mNode);
#endif
					mClosed.push_back(endRecord);
				}

			}
			//# We’ve finished looking at the connections for
			//the current node, so add it to the closed list
			//and remove it from the open list 
			// add +
			for (list<NodeRecord>::iterator iter = mOpen.begin(); iter != mOpen.end(); iter++)
			{
				if (iter->mNode == pCurrentNode.mNode)
				{
					mOpen.erase(iter);
					break;
				}
			}
#ifdef VISUALIZE_PATH
			mVisitedNodes.push_back(pCurrentNode.mNode);
#endif


		}
	}
		gpPerformanceTracker->stopTracking("path");
		mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");
		//We are here if we've found either the goal, or
		//if we have no more nodes to search, find which
		if (pCurrentNode.mNode != pTo)
		{
			//Weve run out of nodes without finding the goal, so no solution
			return NULL;
		}
		//return the reverse path
		while (pCurrentNode.mNode != pFrom)
		{
			mReturnPath->addNode(pCurrentNode.mNode);
			pCurrentNode.mNode = pCurrentNode.mConnection->getFromNode();

			for (list<NodeRecord>::iterator iter = mClosed.begin(); iter != mClosed.end(); iter++)
			{
				if (iter->mNode == pCurrentNode.mNode)
				{
					pCurrentNode.mConnection = iter->mConnection;
					break;
				}
			}
		}
		
	
#ifdef VISUALIZE_PATH
	mpPath = mReturnPath;
#endif

	return mReturnPath;
}
