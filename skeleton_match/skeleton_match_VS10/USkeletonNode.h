#pragma once
#include "m_math.h"
#include "SkeletonGraph.h"
#include <vector>
#include "SkeletonNode.h"

using namespace std;

class USkeletonNode
{
public:
	int id;
	CVector3 point;
	float parentDist;
	USkeletonNode* parent;
	vector<USkeletonNode*> nodes;

	USkeletonNode(void);
	USkeletonNode(int _id, CVector3 _point, USkeletonNode* _parent);
	USkeletonNode(USkeletonNode* root, USkeletonNode* addRoot);
	USkeletonNode(SkeletonGraph* G, int _id = -1);
	USkeletonNode(SkeletonGraph* G, USkeletonNode* root, int gid, int skipId);
	USkeletonNode* SkeletonNodesFromEdge(GraphEdge ge, USkeletonNode* root);
	USkeletonNode(SkeletonGraph* G, USkeletonNode* other, vector<int> mapping);
	USkeletonNode(SkeletonGraph* G, USkeletonNode* root, USkeletonNode* other, vector<int> mapping, int skipId);
	~USkeletonNode(void);

	void SetParent(USkeletonNode* node);
	void RemoveChild(USkeletonNode* node);
	SkeletonNode* ToSkeletonNode();
};

USkeletonNode* SkipSameIds(USkeletonNode* node);

void AddSkeleton(USkeletonNode* oNode, USkeletonNode* aNode, USkeletonNode* root, vector<int> mapping, float lthreshold = 1);


