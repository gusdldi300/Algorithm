
#include <cassert>
#include <stack>

#include "DepthFirstSearch.h"

void DepthFirstSearch::GetPreorderTraversedValues(const std::vector<Node*>& nodes, std::vector<char>* outTraversedValues)
{
    assert(outTraversedValues != nullptr);

    std::unordered_set<const Node*> pNodeVisitedSet;
    
    for (const Node* pStartNode : nodes)
    {
        assert(pStartNode != nullptr);

        if (pNodeVisitedSet.find(pStartNode) != pNodeVisitedSet.end())
        {
            continue;
        }

        std::stack<const Node*> pNodeStack;

        pNodeStack.push(pStartNode);
        pNodeVisitedSet.insert(pStartNode);

        while (pNodeStack.empty() == false)
        {
            const Node* pNode = pNodeStack.top();
            pNodeStack.pop();

            outTraversedValues->push_back(pNode->GetValue());

            for (const Node* pNeighborNode : pNode->GetNeighbors())
            {
                if (pNodeVisitedSet.find(pNeighborNode) != pNodeVisitedSet.end())
                {
                    continue;
                }

                pNodeVisitedSet.insert(pNeighborNode);
                pNodeStack.push(pNeighborNode);
            }
        }
    }

}

void DepthFirstSearch::GetPostorderTraversedValues(const std::vector<Node*>& nodes, std::vector<char>* outTraversedValues)
{
    assert(outTraversedValues != nullptr);

    std::unordered_set<const Node*> pNodeVisitedSet;

    for (const Node* pStartNode : nodes)
    {
        assert(pStartNode != nullptr);

        if (pNodeVisitedSet.find(pStartNode) != pNodeVisitedSet.end())
        {
            continue;
        }

        traversePostorderRecursive(pStartNode, pNodeVisitedSet, outTraversedValues);
    }
}

void DepthFirstSearch::traversePostorderRecursive(const Node* pNode, std::unordered_set<const Node*>& pNodeVisitedSet, std::vector<char>* outTraversedValues)
{
    assert(pNode != nullptr);

    pNodeVisitedSet.insert(pNode);

    for (const Node* pNeighborNode : pNode->GetNeighbors())
    {
        assert(pNeighborNode != nullptr);

        if (pNodeVisitedSet.find(pNeighborNode) != pNodeVisitedSet.end())
        {
            continue;
        }

        traversePostorderRecursive(pNeighborNode, pNodeVisitedSet, outTraversedValues);
    }

    outTraversedValues->push_back(pNode->GetValue());
}