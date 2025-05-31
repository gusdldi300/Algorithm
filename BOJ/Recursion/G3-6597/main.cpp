
#include <cassert>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

#define MAX_NODE_COUNT 26

static int sPreOrderedNodesIndex = 0;

void printPostOrdredNodesRecursive(int startIndex, int endIndex, const std::string& preOrderedNodes, const std::string& inOrderedNodes)
{
    if (startIndex > endIndex)
    {
        return;
    }

    char printNode = preOrderedNodes[sPreOrderedNodesIndex++];
    int nextEndIndex = endIndex;
    for (unsigned int i = startIndex; i <= endIndex; ++i)
    {
        if (inOrderedNodes[i] == printNode)
        {
            nextEndIndex = i;
            break;
        }
    }

    printPostOrdredNodesRecursive(startIndex, nextEndIndex - 1, preOrderedNodes, inOrderedNodes);
    printPostOrdredNodesRecursive(nextEndIndex + 1, endIndex, preOrderedNodes, inOrderedNodes);
    std::cout << printNode;
}

int main()
{
    std::string preOrderedNodes;
    std::string inOrderedNodes;

    while (true)
    {
        std::cin >> preOrderedNodes;
        if (std::cin.eof())
        {
            break;
        }

        std::cin >> inOrderedNodes;
        printPostOrdredNodesRecursive(0, preOrderedNodes.size() - 1, preOrderedNodes, inOrderedNodes);
        
        std::cout << std::endl;
        sPreOrderedNodesIndex = 0;
    }

    return 0;
}


