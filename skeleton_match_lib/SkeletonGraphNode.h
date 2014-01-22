#pragma once
#include <m_math.h>
#include <vector>
#include "GraphEdge.h"

using namespace std;

class SkeletonGraphNode {
public:
	int id;
	CVector3 point;
	vector<SkeletonGraphNode*> neighborhood;
	vector<GraphEdge> edges;
public:
	SkeletonGraphNode(void);
	SkeletonGraphNode(int idx);
	~SkeletonGraphNode(void);

	void AddNeighborWithEdge(SkeletonGraphNode* neighbor, GraphEdge edge);
};

