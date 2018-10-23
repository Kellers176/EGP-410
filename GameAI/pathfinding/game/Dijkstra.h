#pragma once
#include "GridPathfinder.h"
#include <vector>
/*Author: Kelly Herstine
Class: EGP-410
<Section 01>
Assignment: Assignment3
Certification of Authenticity:
I certify that this assignment is entirely my own work.
Purpose: I needed this class in order to impliment Dijkstra for the assignment*/

using namespace std;

class Path;
class Graph;
class GraphicsBuffer;
class Grid;
class Connection;

class Dijkstra :public GridPathfinder
{
public:
	Dijkstra(Graph* pGraph);
	~Dijkstra();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!

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
		
	};
};

