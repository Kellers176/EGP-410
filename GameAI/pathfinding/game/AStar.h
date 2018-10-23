#pragma once
#include "GridPathfinder.h"
#include "Node.h"
#include <vector>
#include <list>
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Purpose: The purpose of this class is to create the AStar pathfinding algorithm. 
I needed to include this in order to be able to make my project work in the way that
I wanted it to.*/

using namespace std;

class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class AStar :public GridPathfinder
{
private:
	/*Purpose of Struct: I included the struct because I needed a way to be able to check the nodes within
	each list and using a struct of NodeRecords was the way that I thought would be best for this*/
	struct NodeRecord : public Trackable
	{
		NodeRecord() : mNode(NULL), mConnection(NULL), mCostSoFar(0) {}
		NodeRecord(Node* myNode, Connection* myConnection, int myCost) : mNode(myNode), mConnection(myConnection), mCostSoFar(myCost) {}

		Node* mNode;
		Connection* mConnection;
		int mCostSoFar;
		int mEstimatedTotalCost;

	};
	/*Purpose of Function: I needed to get the smallest element of the list and I included this in order to iterate
	through the list and find the smallest element inside of it*/
	NodeRecord getSmallestElement(list<NodeRecord> myList);
public:
	AStar(Graph* pGraph);
	~AStar();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!
	/*Purpose of the heuristic: I added this because I wanted to get the Heruistic needed for Astar.
	This function basically gets the estimated total cost of the guesstimated node.*/
	float getHeuristic(Node* pFrom, Node* pTo);


};
