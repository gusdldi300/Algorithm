
#include <iostream>

#define MAX_NODE_COUNT (100001)

void PrintNodesPreOrderedRecursive(int inOrderedStartIndex, int inOrderedEndIndex, int postOrderedStartIndex, int postOrderedEndIndex, const int* inOrderedNodesIndexes, const int* inOrderedNodes, const int* postOrderedNodes)
{
    if (inOrderedStartIndex > inOrderedEndIndex)
    {
        return;
    }

    int parentNode = postOrderedNodes[postOrderedEndIndex];
    int inOrderedNodesParentIndex = inOrderedNodesIndexes[parentNode];

    std::cout << parentNode << ' ';
    int postOrderedLeftEndIndex = postOrderedStartIndex + (inOrderedNodesParentIndex - inOrderedStartIndex) - 1;
    PrintNodesPreOrderedRecursive(inOrderedStartIndex, inOrderedNodesParentIndex - 1, postOrderedStartIndex, postOrderedLeftEndIndex, inOrderedNodesIndexes, inOrderedNodes, postOrderedNodes);
    PrintNodesPreOrderedRecursive(inOrderedNodesParentIndex + 1, inOrderedEndIndex, postOrderedLeftEndIndex + 1, postOrderedEndIndex - 1, inOrderedNodesIndexes, inOrderedNodes, postOrderedNodes);
}

int main()
{
    int nodeCount = 0;
    std::cin >> nodeCount;

    int inOrderedNodes[MAX_NODE_COUNT];
    int inOrderedNodesIndexes[MAX_NODE_COUNT];
    for (int i = 0; i < nodeCount; ++i)
    {
        int node = -1;
        std::cin >> node;
        
        inOrderedNodes[i] = node;
        inOrderedNodesIndexes[node] = i;
    }

    int postOrderedNodes[MAX_NODE_COUNT];
    for (int i = 0; i < nodeCount; ++i)
    {
        std::cin >> postOrderedNodes[i];
    }

    int endIndex = nodeCount - 1;
    PrintNodesPreOrderedRecursive(0, endIndex, 0, endIndex, inOrderedNodesIndexes, inOrderedNodes, postOrderedNodes);

    return 0;
}