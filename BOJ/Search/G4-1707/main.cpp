
#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

#define MAX_NODES_COUNT (20001U)

static bool IsBipartiteGraph(std::vector<unsigned int> nodeGraph[], unsigned int nodesCount)
{
    std::unordered_set<unsigned int> firstNodeSet;
    std::unordered_set<unsigned int> secondNodeSet;

    std::unordered_set<unsigned int>* pNodeSet;
    std::unordered_set<unsigned int>* pOtherNodeSet;

    bool bVisited[MAX_NODES_COUNT] = { false, };
    std::queue<unsigned int> nodeQueue;

    for (unsigned int node = 1; node <= nodesCount; ++node)
    {
        if (bVisited[node])
        {
            continue;
        }

        nodeQueue.push(node);
        bVisited[node] = true;
        firstNodeSet.insert(node);

        unsigned int count = 0;
        while (nodeQueue.empty() == false)
        {
            ++count;

            unsigned int queueSize = nodeQueue.size();
            for (unsigned int i = 0; i < queueSize; ++i)
            {
                unsigned int node = nodeQueue.front();
                nodeQueue.pop();

                if (count % 2 == 0)
                {
                    pNodeSet = &secondNodeSet;
                    pOtherNodeSet = &firstNodeSet;
                }
                else
                {
                    pNodeSet = &firstNodeSet;
                    pOtherNodeSet = &secondNodeSet;
                }

                for (unsigned int neighbor : nodeGraph[node])
                {
                    if (pNodeSet->find(neighbor) != pNodeSet->end())
                    {
                        return false;
                    }

                    if (bVisited[neighbor])
                    {
                        continue;
                    }

                    pOtherNodeSet->insert(neighbor);

                    nodeQueue.push(neighbor);
                    bVisited[neighbor] = true;
                }
            }
        }
    }
    
    return true;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int test = 0; test < testsCount; ++test)
    {
        std::vector<unsigned int> nodeGraph[MAX_NODES_COUNT];

        unsigned int nodesCount;
        unsigned int edgesCount;

        std::cin >> nodesCount >> edgesCount;
        for (unsigned int i = 0; i < edgesCount; ++i)
        {
            unsigned int firstNode;
            unsigned int secondNode;
            
            std::cin >> firstNode >> secondNode;

            nodeGraph[firstNode].push_back(secondNode);
            nodeGraph[secondNode].push_back(firstNode);
        }

        std::cout << (IsBipartiteGraph(nodeGraph, nodesCount) ? "YES" : "NO") << '\n';
    }

    return 0;
}