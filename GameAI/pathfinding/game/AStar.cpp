#include "AStar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Game.h"
#include "GameApp.h"
#include "Vector2D.h"
#include <PerformanceTracker.h>
#include <algorithm>
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.*/

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

	NodeRecord startRecord = NodeRecord();
	//initialize the record for the start node
	startRecord.mNode = pFrom;
	startRecord.mConnection = NULL;
	startRecord.mCostSoFar = 0;
	startRecord.mEstimatedTotalCost = getHeuristic(pFrom, pTo);

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
		//get current node from smallest element
		pCurrentNode = getSmallestElement(mOpen);
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
				//set variables and connections
				float endNodeHeuristic; 
				bool isInClosed = false, isInOpen = false, isVisited = false, check = false;
				Connection* pConnection = connections[i];
				NodeRecord endRecord;
				//get the cost estimate for the end node
				Node* pEndNode = connections[i]->getToNode();
				float endNodeCost = pCurrentNode.mCostSoFar + connections[i]->getCost();

				//assign it also in the closed list so that the graph can display the nodes
				vector<Node*>::iterator temp;
				for (temp = mVisitedNodes.begin(); temp != mVisitedNodes.end(); temp++)
				{
					if ((*temp) == pEndNode)
					{
						isVisited = true;
						break;
					}
				}
				//check if in closed list
				list<NodeRecord>::iterator closed;
				for (list<NodeRecord>::iterator iter = mClosed.begin(); iter != mClosed.end(); iter++)
				{
					if (iter->mNode == pEndNode)
					{
						closed = iter;
						isInClosed = true;
						break;
					}
				}
				//check if in open list
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
				//otherwise we know we've got an unvisited node, so make a record for it
				if (isInClosed)
				{
					//set endRecord to the closed node that we found
					endRecord.mNode = closed->mNode;
					if (endRecord.mCostSoFar <= endNodeCost)
					{
						continue;
					}
					else
					{
						//erase it from the closed list and then get the heusitic
						mVisitedNodes.erase(temp);
						mClosed.erase(closed);
						endNodeHeuristic = getHeuristic(endRecord.mNode, pTo);
					}
				}
				else if (isInOpen)
				{
					//set endRecord to the open node that we found
					endRecord.mNode = tmp->mNode;
					if (endRecord.mCostSoFar <= endNodeCost)
					{
						continue;
					}
					else
					{
						//update the heuristic
						endNodeHeuristic = getHeuristic(endRecord.mNode, pTo);
					}
				}
				else
				{
					//otherwise create a new instance of the endRecord from our PEndNode and update herusitic
					endRecord = NodeRecord(pEndNode, pConnection, endNodeCost);
					endNodeHeuristic = getHeuristic(pEndNode, pTo);
				}
				//update values for the endRecord
				endRecord.mCostSoFar = endNodeCost;
				endRecord.mConnection = pConnection;
				endRecord.mEstimatedTotalCost = endNodeCost + endNodeHeuristic;

				//check if in the open list
				if (!isInOpen)
				{
					//We've finished looking at the connections for the current node, 
					//so add it to the closed list and remove it from the open list
					mOpen.push_back(endRecord);
					
				}
#ifdef VISUALIZE_PATH
					mVisitedNodes.push_back(endRecord.mNode);
#endif
					mClosed.push_front(endRecord);

			}
			//# We’ve finished looking at the connections for
			//the current node, so add it to the closed list
			//and remove it from the open list 
			for (list<NodeRecord>::iterator iter = mOpen.begin(); iter != mOpen.end(); iter++)
			{
				if (iter->mNode == pCurrentNode.mNode)
				{
					mOpen.erase(iter);
					break;
				}
			}

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
	else
	{
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
		mReturnPath->addNode(pFrom);
	}

#ifdef VISUALIZE_PATH
	mpPath = mReturnPath;
#endif



	return mReturnPath;
}

float AStar::getHeuristic(Node * pFrom, Node * pTo)
{
	Grid* pGrid = dynamic_cast<GameApp*>(gpGame)->getGrid();
	Vector2D distance = pGrid->getULCornerOfSquare(pFrom->getId());
	pGrid->getULCornerOfSquare(pTo->getId());

	return distance.getLength();
}

AStar::NodeRecord AStar::getSmallestElement(list<NodeRecord> myList)
{
	float lowest = INFINITY;
	list<NodeRecord>::iterator lowestCost = myList.begin();
	for (list<NodeRecord>::iterator iter = myList.begin(); iter != myList.end(); iter++)
	{
		if (iter->mCostSoFar > lowest)
		{
			lowest = iter->mEstimatedTotalCost;
			lowestCost = iter;

		}
	}
	return (*lowestCost);
}

