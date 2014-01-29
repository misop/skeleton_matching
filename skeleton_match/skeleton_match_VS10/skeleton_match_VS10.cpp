// skeleton_match_VS10.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#pragma warning(push, 0)
#include <boost\archive\archive_exception.hpp>
#include <boost\archive\basic_xml_iarchive.hpp>
#include <boost\archive\xml_iarchive.hpp>
#include <boost\archive\xml_oarchive.hpp>
#pragma pop
#include <iostream>
#include <fstream>
#include <string>
#include "SkeletonMatchNode.h"
#include "GraphMatcher.h"
#include "USkeletonNode.h"

using namespace std;

SkeletonNode* LoadSkeletonFromFile(string fileName) {
	ofstream errorLog("log.txt");
	ifstream inputFile(fileName);
	assert(inputFile.good());
	boost::archive::xml_iarchive inputArchive(inputFile);
	SkeletonNode *node = NULL;
	try {
		inputArchive >> BOOST_SERIALIZATION_NVP(node);	
	} catch (boost::archive::archive_exception e) {
		errorLog << fileName << endl;
		errorLog << "Exception: " << e.what() << endl;
		throw e;
	}
	return node;
}

SkeletonMatchNode* CreateSkeletonA() {
	SkeletonMatchNode* root = new SkeletonMatchNode(0, 0, 0);
	SkeletonMatchNode* node1 = new SkeletonMatchNode(-100, -5, 0);
	SkeletonMatchNode* node2 = new SkeletonMatchNode(-130, 30, 0);
	SkeletonMatchNode* node3 = new SkeletonMatchNode(-130, -30, 0);
	SkeletonMatchNode* node4 = new SkeletonMatchNode(100, -5, 0);
	SkeletonMatchNode* node5 = new SkeletonMatchNode(130, 30, 0);
	SkeletonMatchNode* node6 = new SkeletonMatchNode(130, -30, 0);
	SkeletonMatchNode* node7 = new SkeletonMatchNode(0, 100, 0);

	root->AddChild(node1);
	//root->AddChild(node4);
	root->AddChild(node7);

	node1->AddChild(node2);
	node1->AddChild(node3);

	node4->AddChild(node5);
	node4->AddChild(node6);

	FixParents(root);
	return root;
}

SkeletonMatchNode* CreateSkeletonB() {
	SkeletonMatchNode* root = new SkeletonMatchNode(0, 0, 0);
	SkeletonMatchNode* node1 = new SkeletonMatchNode(-50, -5, 0);
	SkeletonMatchNode* node2 = new SkeletonMatchNode(-130, 30, 0);
	SkeletonMatchNode* node3 = new SkeletonMatchNode(-130, -30, 0);
	SkeletonMatchNode* node4 = new SkeletonMatchNode(50, -5, 0);
	SkeletonMatchNode* node5 = new SkeletonMatchNode(130, 30, 0);
	SkeletonMatchNode* node6 = new SkeletonMatchNode(130, -30, 0);
	SkeletonMatchNode* node7 = new SkeletonMatchNode(0, 100, 0);

	root->AddChild(node1);
	root->AddChild(node4);
	root->AddChild(node7);

	node1->AddChild(node2);
	node1->AddChild(node3);

	node4->AddChild(node5);
	node4->AddChild(node6);

	FixParents(root);
	return root;
}

float AvarageLength(USkeletonNode* root) {
	float length = 0;
	vector<USkeletonNode* > stack;
	stack.push_back(root);

	while (!stack.empty()) {
		USkeletonNode* node = stack.back();
		stack.pop_back();

		length += node->parentDist;

		for (int i = 0; i < node->nodes.size(); i++) {
			stack.push_back(node->nodes[i]);
		}
	}

	return length;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SkeletonNode* sknA = LoadSkeletonFromFile("skeletons/barbie2_24seg_2ite.skl");
	//SkeletonNode* sknB = LoadSkeletonFromFile("skeletons/barbie4_24seg_2ite.skl");
	SkeletonNode* sknB = LoadSkeletonFromFile("skeletons/barbie3_24seg_2ite.skl");
	SkeletonMatchNode* sklA = new SkeletonMatchNode(sknA);
	SkeletonMatchNode* sklB = new SkeletonMatchNode(sknB);
	//SkeletonMatchNode* sklA = CreateSkeletonA();
	//SkeletonMatchNode* sklB = CreateSkeletonB();

	FixParents(sklA);
	FixParents(sklB);

	sklA = PrepareForTriming(sklA);
	sklB = PrepareForTriming(sklB);

	sklA->Trim();
	sklB->Trim();

	int numA = RecalculateIDs(sklA);
	int numB = RecalculateIDs(sklB);

	SkeletonGraph A;
	A.CreateGraphFromSkeleton(sklA, numA);
	SkeletonGraph B;
	B.CreateGraphFromSkeleton(sklB, numB);

	GraphMatcher gm;
	gm.MatchGraphs(&A, &B);
	gm.SortFoundMatchings();

	vector<int> matching = gm.bestMatchings[0];
	USkeletonNode* uroot = new USkeletonNode(&A);
	USkeletonNode* toAdd = new USkeletonNode(&B, uroot, matching);

	float threshold = AvarageLength(uroot) / 10.0;
	AddSkeleton(uroot, toAdd, matching, threshold);

	return 0;
}

