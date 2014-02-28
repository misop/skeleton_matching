#pragma once
#include <m_math.h>
#include <vector>

using namespace std;

struct GraphEdge {
public:
	int nodes;
	float dist;
	vector<int> oldIDs;
	vector<CVector3> positions;
	int fromId;
	int toId;
	GraphEdge() : nodes(0), dist(0) {};
	GraphEdge(int numberOfNodes) : nodes(numberOfNodes), dist(0) {};
	GraphEdge(float distance) : nodes(0), dist(distance) {};
	GraphEdge(int numberOfNodes, float distance) : nodes(numberOfNodes), dist(distance) {};
};