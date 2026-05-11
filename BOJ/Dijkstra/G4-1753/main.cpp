
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>

#define MAX_NODES_COUNT (20001U)

struct Edge
{
public:
    bool operator<(const Edge& other) const
    {
        return Distance > other.Distance;
    }

    unsigned int ToNode;
    unsigned int Distance;
};

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int nodesCount;
    unsigned int edgesCount;

    std::cin >> nodesCount >> edgesCount;

    unsigned int startNode;
    std::cin >> startNode;


    std::vector<Edge> edges[MAX_NODES_COUNT];
    for (unsigned int i = 0; i < edgesCount; ++i)
    {
        unsigned int node;
        unsigned int toNode;
        unsigned int distance;

        std::cin >> node >> toNode >> distance;
        edges[node].push_back({ toNode, distance });
    }
    
    unsigned int minDistances[MAX_NODES_COUNT];
    memset(minDistances, UINT_MAX, sizeof(minDistances));

    minDistances[startNode] = 0;

    std::priority_queue<Edge> edgeQueueAscend;
    edgeQueueAscend.push({ startNode, 0 });

    while (edgeQueueAscend.empty() == false)
    {
        Edge edge = edgeQueueAscend.top();
        edgeQueueAscend.pop();

        if (edge.Distance > minDistances[edge.ToNode])
        {
            continue;
        }

        for (const Edge& nextEdge : edges[edge.ToNode])
        {
            unsigned int accumulatedDistance = minDistances[edge.ToNode] + nextEdge.Distance;

            if (accumulatedDistance >= minDistances[nextEdge.ToNode])
            {
                continue;
            }

            minDistances[nextEdge.ToNode] = minDistances[edge.ToNode] + nextEdge.Distance;
            edgeQueueAscend.push({ nextEdge.ToNode, accumulatedDistance });
        }
    }

    for (unsigned int node = 1; node <= nodesCount; ++node)
    {
        if (minDistances[node] == UINT_MAX)
        {
            std::cout << "INF\n";
            
            continue;
        }

        std::cout << minDistances[node] << '\n';
    }

    return 0;
}