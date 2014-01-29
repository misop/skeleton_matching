#pragma once
#include <vector>
#include <s_skeletonNode.h>

std::vector<SkeletonNode* > MatchSkeletons(std::vector<SkeletonNode *> skeletons, float thresholdPercent = 0.33);