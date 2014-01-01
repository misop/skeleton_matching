#pragma once
#include "m_math.h"
#include <vector>
#include <boost/serialization/version.hpp>

using namespace std;

class SkeletonNode
{
	friend class boost::serialization::access;
public:
	CVector3 point;
	int id;
	vector<float> dists;
	vector<int> betweenNodes;
	vector<SkeletonNode*> nodes;
public:
	SkeletonNode();
	SkeletonNode(float x, float y, float z);
	SkeletonNode(float x, float y, float z, int idx);
	~SkeletonNode(void);

	void AddChild(SkeletonNode *node);
	void Trim();
protected:
	// When the class Archive corresponds to an output archive, the
	// & operator is defined similar to <<.  Likewise, when the class Archive
	// is a type of input archive the & operator is defined similar to >>.
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & BOOST_SERIALIZATION_NVP(id);
		ar & BOOST_SERIALIZATION_NVP(point);
		ar & BOOST_SERIALIZATION_NVP(nodes);
	}
};

BOOST_CLASS_VERSION(SkeletonNode, 2)

	
SkeletonNode* GetEnd(SkeletonNode* node, int &between, float& dist);
int RecalculateIDs(SkeletonNode* node);