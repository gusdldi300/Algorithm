
#include <iostream>

#define MAX_NODE_COUNT (100000)

void PrintNodesPreOrderedRecursive(int startIndex, int endIndex, int postOrderedStartIndex, int postOrderedEndIndex, const int* inOrderedNodes, const int* postOrderedNodes)
{
    if (startIndex > endIndex)
    {
        return;
    }

    int parentNode = postOrderedNodes[postOrderedEndIndex];

    int inOrderedParentIndex = -1;
    for (int i = startIndex; i <= endIndex; ++i)
    {
        if (inOrderedNodes[i] == parentNode)
        {
            inOrderedParentIndex = i;
            break;
        }
    }

    std::cout << parentNode << ' ';

    int postOrderedLeftEndIndex = postOrderedStartIndex + (inOrderedParentIndex - startIndex) - 1;
    PrintNodesPreOrderedRecursive(startIndex, inOrderedParentIndex - 1, postOrderedStartIndex, postOrderedLeftEndIndex, inOrderedNodes, postOrderedNodes);
    PrintNodesPreOrderedRecursive(inOrderedParentIndex + 1, endIndex, postOrderedLeftEndIndex + 1, postOrderedEndIndex - 1, inOrderedNodes, postOrderedNodes);
}

int main()
{
    int nodeCount = 0;
    std::cin >> nodeCount;

    int inOrderedNodes[MAX_NODE_COUNT];
    for (int i = 0; i < nodeCount; ++i)
    {
        std::cin >> inOrderedNodes[i];
    }

    int postOrderedNodes[MAX_NODE_COUNT];
    for (int i = 0; i < nodeCount; ++i)
    {
        std::cin >> postOrderedNodes[i];
    }

    int endIndex = nodeCount - 1;
    PrintNodesPreOrderedRecursive(0, endIndex, 0, endIndex, inOrderedNodes, postOrderedNodes);

    return 0;
}