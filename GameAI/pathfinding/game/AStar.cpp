#include "AStar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Game.h"
#include "GameApp.h"
#include "Vector2D.h"
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
	startRecord.mEstimatedTotalCost = getHeuristic(pFrom, pTo);

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

	Path* mReturnPath = new Path();
	//get current node
	float endNodeHeuristic = 0;
	NodeRecord pCurrentNode;// = NodeRecord();
	bool toNodeAdded = false;

	//Iterate through processing each node
	while (/*pCurrentNode != pTo && */mOpen.size() > 0)
	{
		//get current node from front of list
		//chang to smallest element
		pCurrentNode = getSmallestElement(mOpen);
		//remove node from list
		mOpen.pop_front();
		//mReturnPath->addNode(pCurrentNode.mNode);
		//add Node to Path
		//mReturnPath->addNode(pCurrentNode.mNode);
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
				endNodeHeuristic = 0;
				bool isInClosed = false, isInOpen = false, check = false;
				Connection* pConnection = connections[i];
				NodeRecord endRecord;
				//get the cost estimate for the end node
				Node* pEndNode = connections[i]->getToNode();
				float endNodeCost = pCurrentNode.mCostSoFar + connections[i]->getCost();
				//skip if the node is closed
				/*if (find(mClosed.begin(), mClosed.end(), pEndNode) != mClosed.end())
				{
				continue;
				}*/
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
					endRecord.mNode = closed->mNode;
					if (endRecord.mCostSoFar <= endNodeCost)
					{
						continue;
					}
					else
					{
						mClosed.erase(closed);
						endNodeHeuristic = getHeuristic(endRecord.mNode, pTo);
					}
				}
				else if (isInOpen)
				{
					endRecord.mNode = tmp->mNode;
					if (endRecord.mCostSoFar <= endNodeCost)
					{
						continue;
					}
					else
					{
						endNodeHeuristic = getHeuristic(endRecord.mNode, pTo);
					}
				}
				else
				{

					endRecord = NodeRecord(pEndNode, pConnection, endNodeCost);
					endNodeHeuristic = getHeuristic(pEndNode, pTo);
				}

				endRecord.mCostSoFar = endNodeCost;
				endRecord.mConnection = pConnection;
				endRecord.mEstimatedTotalCost = endNodeCost + endNodeHeuristic;

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
			mClosed.push_back(pCurrentNode);

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

	{

		//Path* myPath = new Path();
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
		//delete myPath;
	}

#ifdef VISUALIZE_PATH
	mpPath = mReturnPath;
#endif



	return mReturnPath;
	//delete mReturnPath;

	return NULL;
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
		if (iter->mCostSoFar < lowest)
		{
			lowest = iter->mEstimatedTotalCost;
			lowestCost = iter;
			
		}
	}
	return (*lowestCost);
}

