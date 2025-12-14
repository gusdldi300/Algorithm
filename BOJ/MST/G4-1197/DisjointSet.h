#pragma once

#include <vector>
#include <unordered_map>

#include "SetNode.h"

class DisjointSet
{
public:
    DisjointSet(const std::vector<unsigned int>& nodes);
    unsigned int FindRootNodeRercursive(unsigned int node) const;
    void Union(unsigned int firstNodeSet, unsigned int secondNodeSet);

private:
    std::unordered_map<unsigned int, SetNode> mSets;
};