#pragma once
#include <vector>
#include <s_skeletonNode.h>
#include <MatchingStruct.h>

std::vector<SkeletonNode* > MatchSkeletons(std::vector<SkeletonNode *> skeletons, std::vector<MatchingStruct>& output, float thresholdPercent = 0.33, float angleThreshold = 20, float axisAngleThreshold = 10, bool symmetric = false);