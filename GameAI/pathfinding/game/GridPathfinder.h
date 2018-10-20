#pragma once

#include "Pathfinder.h"

using namespace std;

class GridGraph;
class GridVisualizer;
class GraphicsBuffer;
class PathfindingDebugContent;

class GridPathfinder:public Pathfinder
{
public:
	friend class PathfindingDebugContent;

	GridPathfinder( GridGraph* pGraph );
	virtual ~GridPathfinder();

	virtual Path* findPath( Node* pFrom, Node* pTo ) = 0;
	
#ifdef VISUALIZE_PATH
	//just for visualization
public:
	void drawVisualization( Grid* pGrid, GraphicsBuffer* pDest );
protected:
	vector<Node*> mVisitedNodes;
	Path* mpPath;
	GridVisualizer* mpVisualizer;
#endif

	double mTimeElapsed;
};