#pragma once
#include "m_math.h"
#include <vector>
#include "GraphEdge.h"

using namespace std;

class SkeletonGraphNode {
public:
	int id;
	vector<SkeletonGraphNode*> neighborhood;
	vector<GraphEdge> edges;
public:
	SkeletonGraphNode(void);
	SkeletonGraphNode(int idx);
	~SkeletonGraphNode(void);

	void AddNeighborWithEdge(SkeletonGraphNode* neighbor, GraphEdge edge);
};

