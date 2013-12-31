#pragma once
#include "SkeletonGraph.h"
#include "GraphNodeMatch.h"

class GraphMatcher
{
public:
	SkeletonGraph* A;
	SkeletonGraph* B;
	int solutions;
	int ignore;
	float bestScore;
	GraphNodeMatch *comparator;

	vector<float> matchingScore;
	vector<int> bestMatching;
	vector<vector<int> > bestMatchings;
	vector<int> used;
public:
	GraphMatcher(void);
	~GraphMatcher(void);

	void MatchGraphs(SkeletonGraph* match, SkeletonGraph* to, GraphNodeMatch* _comparator = NULL, int _solutions = 1, int _ignore = 0);
	void GenerateMatchings();
	void Backtrack(int num, vector<int>& matching);
	bool CanMatch(int a, int b, vector<int>& matching);
	int MatchLeaf(int a, int b, vector<int>& matching);
	void FinishMatching(vector<int>& proposedMatching);
	float ValueMatching(vector<int>& matching);
	void InsertOrdered(float num, vector<int>& matching);
};

bool In(int num, vector<int> array);
