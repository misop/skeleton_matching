#pragma once
#include "m_math.h"
#include <vector>
#include <boost/serialization/version.hpp>

using namespace std;

struct SkeletonNode {
	CVector3 point;
	int id;
	bool cyclic;
	vector<SkeletonNode*> nodes;

	SkeletonNode(){
	}
private:


	friend class boost::serialization::access;
	// When the class Archive corresponds to an output archive, the
	// & operator is defined similar to <<.  Likewise, when the class Archive
	// is a type of input archive the & operator is defined similar to >>.
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version)
	{
		ar  & BOOST_SERIALIZATION_NVP(id);
		ar  & BOOST_SERIALIZATION_NVP(cyclic);
		ar  & BOOST_SERIALIZATION_NVP(point);
		ar  & BOOST_SERIALIZATION_NVP(nodes);
	}

};


BOOST_CLASS_VERSION(SkeletonNode, 0)