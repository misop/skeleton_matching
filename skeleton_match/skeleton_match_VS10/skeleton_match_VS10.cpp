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

int _tmain(int argc, _TCHAR* argv[])
{
	//SkeletonMatchNode* sklA = new SkeletonMatchNode(LoadSkeletonFromFile("skeletons/A.skl"));
	//SkeletonMatchNode* sklB = new SkeletonMatchNode(LoadSkeletonFromFile("skeletons/B.skl"));
	SkeletonMatchNode* sklA = CreateSkeletonA();
	SkeletonMatchNode* sklB = CreateSkeletonB();

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

	return 0;
}

