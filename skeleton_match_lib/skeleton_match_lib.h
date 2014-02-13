#pragma once
#include <map>
#include <vector>
#include <s_skeletonNode.h>
#include <MatchingStruct.h>

std::map<int, MatchingSkeletonStruct> MatchSkeletons(SkeletonNode* skl1, SkeletonNode* skl2);
std::vector<SkeletonNode* > MatchSkeletons(std::vector<SkeletonNode *> skeletons, std::vector<MatchingStruct>& output, float thresholdPercent = 0.33, float angleThreshold = 20, float axisAngleThreshold = 10, bool symmetric = false);