#include "stdafx.h"
#include "GraphMatcher.h"


GraphMatcher::GraphMatcher(void)
{
}


GraphMatcher::~GraphMatcher(void)
{
}

void GraphMatcher::MatchGraphs(SkeletonGraph* match, SkeletonGraph* to, GraphNodeMatch* _comparator, int _solutions, int _ignore) {
	A = match;
	B = to;
	GraphNodeMatch* comp = new GraphNodeMatch();
	comparator = _comparator;
	if (comparator == NULL) comparator = comp;
	solutions = max(1, _solutions);
	ignore = _ignore;
	GenerateMatchings();

	delete comp;
}

void GraphMatcher::GenerateMatchings() {
	vector<int> matching;
	matching.reserve(A->nodes.size());
	used.clear();
	bestMatching.clear();
	bestScore = 0;
	Backtrack(0, matching);
}

void GraphMatcher::Backtrack(int num, vector<int>& matching) {
	if (matching.size() == A->nodes.size()) {
		FinishMatching(matching);
	} else {
		for (int numb = 0; numb <= B->nodes.size(); numb++) {
			int i = numb - 1;
			if (CanMatch(num, i, matching)) {
				matching.push_back(i);
				used.push_back(i);
				if (i == -1) ignore--;
				Backtrack(num + 1, matching);
				used.pop_back();
				matching.pop_back();
				if (i == -1) ignore++;
			}
		}
	}
}

bool GraphMatcher::CanMatch(int a, int b, vector<int>& matching) {
	if (b == -1) {
		if (ignore < 0 || ignore > 0)
			return true;
		else
			return false;
	} else {
		if (!In(b, used) && comparator->CanMatch(A, B, a, b, matching)) {
			return true;
		}
	}

	return false;
}

void GraphMatcher::FinishMatching(vector<int>& proposedMatching) {
	/*//proposed matching only matches branch nodes
	//we need to create matching for leaf nodes
	//empty matching
	vector<int> finalMatching;
	finalMatching.reserve(A->nodes.size());
	for (int i = 0; i < A->nodes.size(); i++) {
		finalMatching.push_back(-1);
	}
	//first add branch nodes
	for (int i = 0; i < proposedMatching.size(); i++) {
		finalMatching[A->branchNodes[i]->id] = proposedMatching[i];
	}
	//then add all leaf combinations
	vector<int> tempUsed = used;
	for (int i = 0; i < A->branchNodes.size(); i++) {
		for (int j = 0; j < A->branchNodes[i]->neighborhood.size(); j++) {
			SkeletonGraphNode* node = A->branchNodes[i]->neighborhood[j];
			//we need to match leafs
			if (node->neighborhood.size() == 1) {
				int idx = MatchLeaf(node->id, finalMatching[A->branchNodes[i]->id], finalMatching);
				finalMatching[node->id] = idx;
			}
		}
	}
	//for now
	float error = ValueMatching(finalMatching);
	if (bestMatchings.size() < solutions || error < matchingScore.back()) {
		//bestScore = error;
		//bestMatching = finalMatching;
		InsertOrdered(error, finalMatching);
		if (bestMatchings.size() > solutions) {
			bestMatchings.resize(solutions);
		}
	}
	//and restore used
	used = tempUsed;*/
	float error = ValueMatching(proposedMatching);
	if (bestMatchings.size() < solutions || error < matchingScore.back()) {
		//bestScore = error;
		//bestMatching = finalMatching;
		InsertOrdered(error, proposedMatching);
		if (bestMatchings.size() > solutions) {
			bestMatchings.resize(solutions);
		}
	}
}

void GraphMatcher::InsertOrdered(float num, vector<int>& matching) {
	if (matchingScore.size() == 0 || num >= matchingScore.back()) {
		matchingScore.push_back(num);
		bestMatchings.push_back(matching);
		return;
	}
	vector<vector<int> >::iterator it_2 = bestMatchings.begin();
	for (vector<float>::iterator it = matchingScore.begin(); it != matchingScore.end(); it++) {
		if ((*it) > num) {
			matchingScore.insert(it, num);
			bestMatchings.insert(it_2, matching);
			break;
		}

		it_2++;
	}
}

//get ID in B for node from A
int GraphMatcher::MatchLeaf(int a, int b, vector<int>& matching) {
	for (int i = 0; i < B->nodes[b]->neighborhood.size(); i++) {
		SkeletonGraphNode* node = B->nodes[b]->neighborhood[i];
		//node was not used
		if (!In(node->id, used)) {
			used.push_back(node->id);
			return node->id;
		}
	}

	return -1;
}

float GraphMatcher::ValueMatching(vector<int>& matching) {
	float error = 0;

	for (int i = 0; i < A->nodes.size(); i++) {
		SkeletonGraphNode* node = A->nodes[i];
		if (matching[i] == -1) {
			//if the node is not mapped add all his neighbors as error
			for (int j = 0; j < node->edges.size(); j++) {
				error += node->edges[j].nodes;
			}
		} else {
			//error are only the missing ones
			//find matches
			vector<int> matched;
			for (int j = 0; j < node->neighborhood.size(); j++) {
				matched.push_back(node->neighborhood[j]->id);
			}
			//check if matches are neighbors and add error
			for (int j = 0; j < matched.size(); j++) {
				if (matching[matched[j]] == -1) {
					//penalize for missing neighbor
					error += 10;
				} else {
					GraphEdge edge;
					if (B->AreNeighbors(matching[node->id], matching[matched[j]], edge)) {
						error += abs(edge.nodes - node->edges[j].nodes);
					} else {//penalize for wrong topology
						error += 100;
					}
				}
			}
		}
	}

	return error;
}

bool In(int num, vector<int> array) {
	for (int i = 0; i < array.size(); i++) {
		if (num == array[i]) return true;
	}

	return false;
}
