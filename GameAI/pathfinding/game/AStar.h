#pragma once

#include "GridPathfinder.h"
#include "Node.h"
#include <vector>
#include <list>
<<<<<<< HEAD
=======

>>>>>>> 8c686fda37813f63ba6299684d0ea171abb71368
using namespace std;

class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class AStar :public GridPathfinder
{
private:
	struct NodeRecord : public Trackable
	{
		NodeRecord() : mNode(NULL), mConnection(NULL), mCostSoFar(0) {}
		NodeRecord(Node* myNode, Connection* myConnection, int myCost) : mNode(myNode), mConnection(myConnection), mCostSoFar(myCost) {}

		Node* mNode;
		Connection* mConnection;
		int mCostSoFar;
		int mEstimatedTotalCost;

	};
	NodeRecord getSmallestElement(list<NodeRecord> myList);
public:
	AStar(Graph* pGraph);
	~AStar();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!

	float getHeuristic(Node* pFrom, Node* pTo);


};
