#include "stdafx.h"
#include "SkeletonGraphNode.h"


SkeletonGraphNode::SkeletonGraphNode(void)
{
}

SkeletonGraphNode::SkeletonGraphNode(int idx) : id(idx)
{
}

SkeletonGraphNode::~SkeletonGraphNode(void)
{
}

void SkeletonGraphNode::AddNeighborWithEdge(SkeletonGraphNode* neighbor, GraphEdge edge) {
	neighborhood.push_back(neighbor);
	edges.push_back(edge);
}
