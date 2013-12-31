#pragma once
#include "SkeletonGraphNode.h"

class GraphNodeCompare
{
public:
	GraphNodeCompare(void);
	~GraphNodeCompare(void);

	bool CanMatch(SkeletonGraphNode* a, SkeletonGraphNode* b) {
		return (a->neighborhood.size() == b->neighborhood.size());
	}
};

