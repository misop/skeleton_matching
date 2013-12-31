#pragma once
#include "SkeletonGraphNode.h"
#include "SkeletonNode.h"

class SkeletonGraph
{
public:
	vector<SkeletonGraphNode*> nodes;
	vector<SkeletonGraphNode*> branchNodes;
public:
	SkeletonGraph(void);
	~SkeletonGraph(void);

	void CreateGraphFromSkeleton(SkeletonNode* root, int numOfNodes);
	void CollectBranchNodes();
	
	void AddNode(SkeletonGraphNode* node);
	void CreateEdge(int i, int j, GraphEdge edge);
	void FreeNodes();
	bool AreNeighbors(int i, int j, GraphEdge& edge);
};

