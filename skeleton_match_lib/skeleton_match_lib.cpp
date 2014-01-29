#include "skeleton_match_lib.h"
#include <string>
#include "SkeletonMatchNode.h"
#include "GraphMatcher.h"
#include "USkeletonNode.h"

using namespace std;

float AvarageLength(USkeletonNode* root) {
	float length = 0;
	float nodes = 0;
	vector<USkeletonNode* > stack;
	stack.push_back(root);

	while (!stack.empty()) {
		USkeletonNode* node = stack.back();
		stack.pop_back();

		length += node->parentDist;
		nodes += 1;

		for (int i = 0; i < node->nodes.size(); i++) {
			stack.push_back(node->nodes[i]);
		}
	}

	return length/nodes;
}

vector<SkeletonNode* > MatchSkeletons(vector<SkeletonNode *> skeletons, float thresholdPercent) {
	vector<SkeletonMatchNode *> skls;
	for (int i = 0; i < skeletons.size(); i++) {
		SkeletonMatchNode* skl = new SkeletonMatchNode(skeletons[i]);
		FixParents(skl);
		skl = PrepareForTriming(skl);
		skl->Trim();
		skls.push_back(skl);
	}

	vector<SkeletonGraph* > G;
	for (int i = 0; i < skls.size(); i++) {
		int nodes = RecalculateIDs(skls[i]);
		SkeletonGraph* A = new SkeletonGraph();
		A->CreateGraphFromSkeleton(skls[i], nodes);
		G.push_back(A);
	}

	int smalestID = 0;
	int snodes = 0;
	for (int i = 0; i < G.size(); i++) {
		if (i == 0 || snodes > G[i]->nodes.size()) {
			snodes = G[i]->nodes.size();
			smalestID = i;
		}
	}
	vector<vector<int> > mappings;
	for (int i = 0; i < G.size(); i++) {
		GraphMatcher gm;
		gm.MatchGraphs(G[smalestID], G[i]);
		gm.SortFoundMatchings();
		mappings.push_back(gm.bestMatchings[0]);
	}

	USkeletonNode* uroot = new USkeletonNode(G[smalestID]);
	vector<USkeletonNode* > skelets;
	float threshold = AvarageLength(uroot) * thresholdPercent;
	for (int i = 0; i < G.size(); i++) {
		USkeletonNode* toAdd = new USkeletonNode(G[i], uroot, mappings[i]);
		//AddSkeleton(uroot, toAdd, uroot, mappings[i]);
		AddSkeleton(uroot, toAdd, mappings[i], threshold);
		skelets.push_back(toAdd);
	}

	vector<SkeletonNode* > result;
	result.push_back(uroot->ToSkeletonNode());
	for (int i = 0; i < skelets.size(); i++) {
		//result.push_back(skelets[i]->ToSkeletonNode());
		AddSkeleton(skelets[i], uroot, mappings[i], threshold);
		result.push_back(skelets[i]->ToSkeletonNode());
	}

	for (int i = 0; i < skls.size(); i++) {
		delete skls[i];
	}
	for (int i = 0; i < G.size(); i++) {
		delete G[i];
	}
	for (int i = 0; i < skelets.size(); i++) {
		delete skelets[i];
	}
	delete uroot;

	return result;
}