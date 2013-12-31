#include "stdafx.h"
#include "SkeletonNode.h"
#include <deque>

SkeletonNode::SkeletonNode (void) : point(CVector3()), id(0) {
}

SkeletonNode::SkeletonNode(float x, float y, float z) : point(CVector3(x, y, z)), id(0) {
}

SkeletonNode::SkeletonNode(float x, float y, float z, int idx) : point(CVector3(x, y, z)), id(idx) {
}

SkeletonNode::~SkeletonNode (void) {
	for (int i = 0; i < nodes.size(); i++) {
		delete nodes[i];
	}
}

void SkeletonNode::AddChild(SkeletonNode *node) {
	nodes.push_back(node);
}

//trims the skeleton and stores distance and number of nodes in the original skeleton
void SkeletonNode::Trim() {
	dists.clear();
	betweenNodes.clear();

	for (int i = 0; i < nodes.size(); i++) {
		int between = 0;
		float dist = 0;
		SkeletonNode* node = GetEnd(nodes[i], between, dist);
		nodes[i] = node;
		betweenNodes.push_back(between);
		dists.push_back(dist);
	}

	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->Trim();
	}
}

//finds the last link
SkeletonNode* GetEnd(SkeletonNode* node, int &between, float& dist) {
	SkeletonNode* search = node;
	between = 0;
	dist = 0;

	while (search->nodes.size() == 1) {
		between++;
		dist += Length(search->point - search->nodes[0]->point);
		search = search->nodes[0];
	}

	return search;
}

int RecalculateIDs(SkeletonNode* node) {
	deque<SkeletonNode*> queue;
	queue.push_back(node);
	int id = 0;

	while (!queue.empty()) {
		SkeletonNode* aNode = queue.front();
		queue.pop_front();

		aNode->id = id;
		id++;

		for (int i = 0; i < aNode->nodes.size(); i++) {
			queue.push_back(aNode->nodes[i]);
		}
	}

	return id;
}
