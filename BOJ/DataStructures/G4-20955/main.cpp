#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>

#define MAX_NODES_COUNT (10001U)

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int nodesCount;
    unsigned int edgesCount;

    std::cin >> nodesCount >> edgesCount;

    std::unordered_set<unsigned int> connectedNodeSet[MAX_NODES_COUNT];

    for (unsigned int i = 0; i < edgesCount; ++i)
    {
        unsigned int firstNode;
        unsigned int secondNode;

        std::cin >> firstNode >> secondNode;

        connectedNodeSet[firstNode].insert(secondNode);
        connectedNodeSet[secondNode].insert(firstNode);
    }

    unsigned int treesCount = 0;
    unsigned int operationsCount = 0;

    bool bVisited[MAX_NODES_COUNT] = { false, };
    for (unsigned int node = 1; node <= nodesCount; ++node)
    {
        if (bVisited[node])
        {
            continue;
        }

        // Make a tree
        {
            std::stack<unsigned int> parentNodeStack;
            parentNodeStack.push(0);

            std::stack<unsigned int> nodeStack;
            nodeStack.push(node);
            bVisited[node] = true;

            while (nodeStack.empty() == false)
            {
                unsigned int newNode = nodeStack.top();
                nodeStack.pop();

                for (unsigned int nextNode : connectedNodeSet[newNode])
                {
                    connectedNodeSet[nextNode].erase(newNode);

                    if (bVisited[nextNode])
                    {
                        ++operationsCount;

                        continue;
                    }

                    nodeStack.push(nextNode);
                    bVisited[nextNode] = true;
                }
            }
        }

        ++treesCount;
    }

    operationsCount += (treesCount - 1);
    std::cout << operationsCount;

    return 0;
}