#pragma once

#include <unordered_set>

#include "Node.h"

class DepthFirstSearch
{
public:
    static void GetPreorderTraversedValues(const std::vector<Node*>& nodes, std::vector<char>* outTraversedValues);
    static void GetPostorderTraversedValues(const std::vector<Node*>& nodes, std::vector<char>* outTraversedValues);
    
private:
    static void traversePostorderRecursive(const Node* pNode, std::unordered_set<const Node*>& pNodeVisitedSet, std::vector<char>* outTraversedValues);
};

