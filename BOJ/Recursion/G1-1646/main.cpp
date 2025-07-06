
#include <iostream>
#include <string>
#include <cassert>

#define MAX_NODES_COUNT (50)

unsigned int FillTreeNodeCountsRecursive(unsigned int treeNode, unsigned long long* visitedTreeNodeCounts)
{
    if (visitedTreeNodeCounts[treeNode] > 0)
    {
        return visitedTreeNodeCounts[treeNode];
    }

    unsigned long long leftChildCount = FillTreeNodeCountsRecursive(treeNode - 2, visitedTreeNodeCounts);
    unsigned long long rightChildCount = FillTreeNodeCountsRecursive(treeNode - 1, visitedTreeNodeCounts);

    visitedTreeNodeCounts[treeNode] = 1LL + leftChildCount + rightChildCount;
}

void SearchNodeRecursive(unsigned int currentSearchSequence, const unsigned int searchSequence, unsigned int currentNode, std::string* outSearchPaths, const unsigned long long* visitedTreeNodeCounts)
{
    if (currentSearchSequence == searchSequence)
    {
        return;
    }

    unsigned long long medianSequence = currentSearchSequence + visitedTreeNodeCounts[currentNode - 2];
    if (searchSequence <= medianSequence)
    {
        outSearchPaths->append("L");
        SearchNodeRecursive(currentSearchSequence + 1, searchSequence, currentNode - 2, outSearchPaths, visitedTreeNodeCounts);
    }
    else
    {
        outSearchPaths->append("R");
        SearchNodeRecursive(medianSequence + 1, searchSequence, currentNode - 1, outSearchPaths, visitedTreeNodeCounts);
    }
}

int main()
{
    unsigned int treeNode = 0;
    unsigned int startSearchSequence = 0;
    unsigned int endSearchSequence = 0;

    std::cin >> treeNode >> startSearchSequence >> endSearchSequence;
    
    assert(treeNode <= 50);
    assert(startSearchSequence > 0);
    assert(endSearchSequence > 0);

    unsigned long long visitedTreeNodeCounts[MAX_NODES_COUNT + 1] = { 0, };
    visitedTreeNodeCounts[0] = 1;
    visitedTreeNodeCounts[1] = 1;

    FillTreeNodeCountsRecursive(treeNode, visitedTreeNodeCounts);
    
    std::string startNodePaths;
    SearchNodeRecursive(1, startSearchSequence, treeNode, &startNodePaths, visitedTreeNodeCounts);
    
    std::string endNodePaths;
    SearchNodeRecursive(1, endSearchSequence, treeNode, &endNodePaths, visitedTreeNodeCounts);

    std::string shortestPaths;
    //shortestPaths.reserve(startNodePaths.size() + endNodePaths.size());

    const char* startPathsPtr = startNodePaths.c_str();
    const char* endPathsPtr = endNodePaths.c_str();
    while (true)
    {
        char startPath = *startPathsPtr;
        char endPath = *endPathsPtr;

        if (startPath == '\0' || endPath == '\0')
        {
            break;
        }

        if (startPath != endPath)
        {
            break;
        }

        startPathsPtr++;
        endPathsPtr++;
    }

    while (*startPathsPtr != '\0')
    {
        shortestPaths.append("U");
        startPathsPtr++;
    }

    while (true)
    {
        char endPath = *endPathsPtr;
        if (endPath == '\0')
        {
            break;
        }

        shortestPaths.push_back(endPath);
        endPathsPtr++;
    }

    std::cout << shortestPaths;

    return 0;
}