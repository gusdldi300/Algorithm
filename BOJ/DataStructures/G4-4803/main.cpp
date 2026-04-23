#include <iostream>
#include <vector>

#define MAX_NODES_COUNT (501)

static bool IsTree(unsigned int lastNode, unsigned int node, bool bVisited[], std::vector<unsigned int> connectedNodeList[])
{
    if (bVisited[node])
    {
        return false;
    }
    
    bVisited[node] = true;

    for (unsigned int childNode : connectedNodeList[node])
    {
        if (childNode == lastNode)
        {
            continue;
        }

        if (IsTree(node, childNode, bVisited, connectedNodeList) == false)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testCase = 1;

    while (true)
    {
        unsigned int nodesCount;
        unsigned int edgesCount;
        std::cin >> nodesCount >> edgesCount;

        if (nodesCount == 0)
        {
            break;
        }

        std::vector<unsigned int> connectedNodeList[MAX_NODES_COUNT];
        for (unsigned int i = 0; i < edgesCount; ++i)
        {
            unsigned int firstNode;
            unsigned int secondNode;

            std::cin >> firstNode >> secondNode;
            
            connectedNodeList[firstNode].push_back(secondNode);
            connectedNodeList[secondNode].push_back(firstNode);
        }

        unsigned int treesCount = 0;
        bool bVisited[MAX_NODES_COUNT] = { false, };

        for (unsigned int node = 1; node <= nodesCount; ++node)
        {
            if (bVisited[node])
            {
                continue;
            }

            if (IsTree(0, node, bVisited, connectedNodeList))
            {
                ++treesCount;
            }
        }

        std::cout << "Case " << testCase << ": ";

        if (treesCount == 0)
        {
            std::cout << "No trees." << '\n';
               
        }
        else if (treesCount == 1)
        {
            std::cout << "There is one tree." << '\n';
        }
        else
        {
            std::cout << "A forest of " << treesCount << " trees." << '\n';
        }

        ++testCase;
    }
    
    return 0;
}