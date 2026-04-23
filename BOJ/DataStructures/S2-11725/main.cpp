#include <vector>
#include <iostream>
#include <queue>

#define MAX_NODES_COUNT (100001U)

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int nodesCount;
    std::cin >> nodesCount;

    std::vector<unsigned int> connectedNodes[MAX_NODES_COUNT];
    for (unsigned int i = 0; i < nodesCount - 1; ++i)
    {
        unsigned int firstNode;
        unsigned int secondNode;

        std::cin >> firstNode >> secondNode;

        connectedNodes[firstNode].push_back(secondNode);
        connectedNodes[secondNode].push_back(firstNode);
    }

    const unsigned int rootNode = 1;

    unsigned int parentNodes[MAX_NODES_COUNT] = { 0, };
    bool bVisited[MAX_NODES_COUNT] = { false, };
    std::queue<unsigned int> nodeQueue;

    nodeQueue.push(rootNode);
    bVisited[rootNode] = true;

    while (nodeQueue.empty() == false)
    {
        unsigned int node = nodeQueue.front();
        nodeQueue.pop();

        for (unsigned int childNode : connectedNodes[node])
        {
            if (bVisited[childNode])
            {
                continue;
            }

            parentNodes[childNode] = node;

            nodeQueue.push(childNode);
            bVisited[childNode] = true;
        }
    }

    for (unsigned int node = 2; node <= nodesCount; ++node)
    {
        std::cout << parentNodes[node] << '\n';
    }
    
    return 0;
}