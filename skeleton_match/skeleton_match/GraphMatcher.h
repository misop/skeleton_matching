#pragma once
#include "SkeletonGraph.h"

class GraphMatcher
{
public:
	SkeletonGraph* A;
	SkeletonGraph* B;
	int solutions;
	int ignore;
	float bestScore;

	vector<float> matchingScore;
	vector<int> bestMatching;
	vector<int> used;
public:
	GraphMatcher(void);
	~GraphMatcher(void);

	void MatchGraphs(SkeletonGraph* match, SkeletonGraph* to, int _solutions = 1, int _ignore = 0);
	void GenerateMatchings();
	void Backtrack(int num, vector<int>& matching);
	bool CanMatch(int a, int b);
	int MatchLeaf(int a, int b, vector<int>& matching);
	void FinishMatching(vector<int>& proposedMatching, vector<int>& finalMatching);
	float ValueMatching(vector<int>& matching);
};

bool In(int num, vector<int> array);

