
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_NODES_COUNT (100001U)

static std::vector<unsigned int> sConnectedNodeList[MAX_NODES_COUNT];
static unsigned int sSubtreeNodeCounts[MAX_NODES_COUNT];

static unsigned int SetSubTreeNodeCountRecursive(unsigned int node)
{
    sSubtreeNodeCounts[node] = 1;
    for (unsigned int childNode : sConnectedNodeList[node])
    {
        if (sSubtreeNodeCounts[childNode] != UINT_MAX)
        {
            continue;
        }

        sSubtreeNodeCounts[node] += SetSubTreeNodeCountRecursive(childNode);
    }

    return sSubtreeNodeCounts[node];
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int nodesCount;
    unsigned int rootNode;
    unsigned int queriesCount;

    std::cin >> nodesCount >> rootNode >> queriesCount;
    
    for (unsigned int i = 0; i < nodesCount - 1; ++i)
    {
        unsigned int firstNode;
        unsigned int secondNode;
        
        std::cin >> firstNode >> secondNode;

        sConnectedNodeList[firstNode].push_back(secondNode);
        sConnectedNodeList[secondNode].push_back(firstNode);
    }

    memset(sSubtreeNodeCounts, UINT_MAX, sizeof(sSubtreeNodeCounts));
    SetSubTreeNodeCountRecursive(rootNode);

    for (unsigned int i = 0; i < queriesCount; ++i)
    {
        unsigned int queryNode;
        std::cin >> queryNode;

        std::cout << sSubtreeNodeCounts[queryNode] << '\n';
    }

    return 0;
}