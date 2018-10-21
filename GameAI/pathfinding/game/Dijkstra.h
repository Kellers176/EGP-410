#pragma once

#include "GridPathfinder.h"
#include <vector>
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
	struct NodeRecord : public Trackable
	{
		NodeRecord() : mNode(NULL), mConnection(NULL), mCostSoFar(0) {}
		NodeRecord(Node* myNode, Connection* myConnection, int myCost) : mNode(myNode), mConnection(myConnection), mCostSoFar(myCost) {}

		Node* mNode;
		Connection* mConnection;
		int mCostSoFar;
		
	};
};

