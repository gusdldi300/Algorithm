#include <iostream>
#include <vector>
#include <queue>

#define MAX_NODES_COUNT (1001U)

struct EdgeInfo
{
    unsigned int Node;
    unsigned int Distance;
};

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int nodesCount;
    unsigned int queriesCount;

    std::vector<EdgeInfo> edges[MAX_NODES_COUNT];
    
    std::cin >> nodesCount >> queriesCount;
    for (unsigned int i = 0; i < nodesCount - 1; ++i)
    {
        unsigned int firstNode;
        unsigned int secondNode;
        unsigned int value;

        std::cin >> firstNode >> secondNode >> value;
        edges[firstNode].push_back({ secondNode, value });
        edges[secondNode].push_back({ firstNode, value });
    }

    for (unsigned int i = 0; i < queriesCount; ++i)
    {
        unsigned int startNode;
        unsigned int endNode;
        
        std::cin >> startNode >> endNode;
        
        std::queue<EdgeInfo> edgeInfoQueue;
        bool bVisited[MAX_NODES_COUNT] = { false, };

        edgeInfoQueue.push({ startNode, 0 });
        bVisited[startNode] = true;
        
        unsigned int edgeDistance = 0;
        while (edgeInfoQueue.empty() == false)
        {
            EdgeInfo edge = edgeInfoQueue.front();
            edgeInfoQueue.pop();

            if (edge.Node == endNode)
            {
                edgeDistance = edge.Distance;

                break;
            }

            for (const EdgeInfo& nextEdge : edges[edge.Node])
            {
                if (bVisited[nextEdge.Node])
                {
                    continue;
                }

                edgeInfoQueue.push({ nextEdge.Node, edge.Distance + nextEdge.Distance });
                bVisited[nextEdge.Node] = true;
            }
        }

        std::cout << edgeDistance << '\n';
    }

    return 0;
}