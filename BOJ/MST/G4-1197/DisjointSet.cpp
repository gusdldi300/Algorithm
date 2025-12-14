
#include <cassert>

#include "DisjointSet.h"

DisjointSet::DisjointSet(const std::vector<unsigned int>& nodes)
{
    for (unsigned int node : nodes)
    {
        SetNode nodeSet(node, 1);
        mSets.insert(std::pair<unsigned int, SetNode>(node, nodeSet));
    }
}

unsigned int DisjointSet::FindRootNodeRercursive(unsigned int node) const
{
    auto nodeSetIter = mSets.find(node);
    
    assert(nodeSetIter != mSets.end());

    SetNode nodeSet = nodeSetIter->second;
    unsigned int parentNode = nodeSet.GetParentNode();
    if (parentNode == node)
    {
        return node;
    }

    nodeSet.SetParentNode(FindRootNodeRercursive(parentNode));

    return nodeSet.GetParentNode();
}

void DisjointSet::Union(unsigned int firstNodeSet, unsigned int secondNodeSet)
{
    unsigned int firstRootNode = FindRootNodeRercursive(firstNodeSet);
    unsigned int secondRootNode = FindRootNodeRercursive(secondNodeSet);

    if (firstRootNode == secondRootNode)
    {
        return;
    }

    assert(mSets.find(firstRootNode) != mSets.end());
    assert(mSets.find(secondRootNode) != mSets.end());

    SetNode* pParentSetNode = &(mSets.find(firstRootNode)->second);
    SetNode* pChildSetNode = &(mSets.find(secondRootNode)->second);

    if (pParentSetNode->GetSize() < pChildSetNode->GetSize())
    {
        SetNode* pTemp = pParentSetNode;

        pParentSetNode = pChildSetNode;
        pChildSetNode = pTemp;
    }

    pChildSetNode->SetParentNode(pParentSetNode->GetParentNode());
    pParentSetNode->SetSize(pParentSetNode->GetSize() + pChildSetNode->GetSize());
}
