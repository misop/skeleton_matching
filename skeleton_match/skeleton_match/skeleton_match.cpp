// skeleton_match.cpp : Defines the entry point for the console application.
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

SkeletonNode* CreateSkeletonA() {
	SkeletonNode* root = new SkeletonNode(0, 0, 0);
	SkeletonNode* node1 = new SkeletonNode(-100, -5, 0);
	SkeletonNode* node2 = new SkeletonNode(-130, 30, 0);
	SkeletonNode* node3 = new SkeletonNode(-130, -30, 0);
	SkeletonNode* node4 = new SkeletonNode(100, -5, 0);
	SkeletonNode* node5 = new SkeletonNode(130, 30, 0);
	SkeletonNode* node6 = new SkeletonNode(130, -30, 0);
	SkeletonNode* node7 = new SkeletonNode(0, 100, 0);
	
	root->AddChild(node1);
	root->AddChild(node4);
	root->AddChild(node7);
	
	node1->AddChild(node2);
	node1->AddChild(node3);
	
	node4->AddChild(node5);
	node4->AddChild(node6);

	return root;
}

SkeletonNode* CreateSkeletonB() {
	SkeletonNode* root = new SkeletonNode(0, 0, 0);
	SkeletonNode* node1 = new SkeletonNode(-50, -5, 0);
	SkeletonNode* node2 = new SkeletonNode(-130, 30, 0);
	SkeletonNode* node3 = new SkeletonNode(-130, -30, 0);
	SkeletonNode* node4 = new SkeletonNode(50, -5, 0);
	SkeletonNode* node5 = new SkeletonNode(130, 30, 0);
	SkeletonNode* node6 = new SkeletonNode(130, -30, 0);
	SkeletonNode* node7 = new SkeletonNode(0, 100, 0);
	
	root->AddChild(node1);
	root->AddChild(node4);
	root->AddChild(node7);
	
	node1->AddChild(node2);
	node1->AddChild(node3);
	
	node4->AddChild(node5);
	node4->AddChild(node6);

	return root;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//SkeletonNode* sklA = LoadSkeletonFromFile("skeletons/A.skl");
	//SkeletonNode* sklB = LoadSkeletonFromFile("skeletons/B.skl");
	SkeletonNode* sklA = CreateSkeletonA();
	SkeletonNode* sklB = CreateSkeletonB();

	sklA->Trim();
	sklB->Trim();
	
	int numA = RecalculateIDs(sklA);
	int numB = RecalculateIDs(sklB);
	
	SkeletonGraph A;
	A.CreateGraphFromSkeleton(sklA, numA);
	SkeletonGraph B;
	B.CreateGraphFromSkeleton(sklB, numB);

	GraphMatcher gm;
	gm.MatchGraphs(&A, &B, &GraphNodeMatch(), 4);

	return 0;
}

