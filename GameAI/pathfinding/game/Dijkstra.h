#pragma once

#include "GridPathfinder.h"
#include <vector>


class Path;
class Graph;
class GraphicsBuffer;
class Grid;

class Dijkstra :public GridPathfinder
{
public:
	Dijkstra(Graph* pGraph);
	~Dijkstra();

	Path* findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!

private:
};

