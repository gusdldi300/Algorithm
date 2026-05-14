
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>

#define MAX_NODES_COUNT (801U)
#define MAX_DISTANCE (1001U)

#define MAX_ACCUMULATED_DISTANCE (MAX_NODES_COUNT * MAX_DISTANCE)

struct Destination
{
    bool operator<(const Destination& other) const
    {
        return Distance > other.Distance;
    }

    unsigned int Node;
    long long Distance;
};

void GetShortestDistances(unsigned int startNode, long long outShortestDistances[], const std::vector<Destination> destinations[])
{
    outShortestDistances[startNode] = 0;

    std::priority_queue<Destination> destinationQueueDistanceAscend;
    destinationQueueDistanceAscend.push({ startNode, 0 });

    while (destinationQueueDistanceAscend.empty() == false)
    {
        Destination accumulatedDestination = destinationQueueDistanceAscend.top();
        destinationQueueDistanceAscend.pop();

        if (accumulatedDestination.Distance > outShortestDistances[accumulatedDestination.Node])
        {
            continue;
        }

        for (const Destination& nextDestination : destinations[accumulatedDestination.Node])
        {
            long long accumulatedDistance = accumulatedDestination.Distance + nextDestination.Distance;
            
            if (accumulatedDistance >= outShortestDistances[nextDestination.Node])
            {
                continue;
            }

            destinationQueueDistanceAscend.push({ nextDestination.Node, accumulatedDistance });
            outShortestDistances[nextDestination.Node] = accumulatedDistance;
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int nodesCount;
    unsigned int edgesCount;

    std::vector<Destination> destinations[MAX_NODES_COUNT];

    std::cin >> nodesCount >> edgesCount;
    for (unsigned int i = 0; i < edgesCount; ++i)
    {
        unsigned int startNode;
        unsigned int endNode;
        long long distance;

        std::cin >> startNode >> endNode >> distance;

        destinations[startNode].push_back({ endNode, distance });
        destinations[endNode].push_back({ startNode, distance });
    }

    unsigned int firstPathNode;
    unsigned int secondPathNode;

    std::cin >> firstPathNode >> secondPathNode;

    long long startNodeShortestDistances[MAX_NODES_COUNT];
    std::fill(startNodeShortestDistances, startNodeShortestDistances + MAX_NODES_COUNT, INT_MAX);

    long long firstPathNodeShortestDistances[MAX_NODES_COUNT];
    std::fill(firstPathNodeShortestDistances, firstPathNodeShortestDistances + MAX_NODES_COUNT, INT_MAX);

    long long secondPathNodeShortestDistances[MAX_NODES_COUNT];
    std::fill(secondPathNodeShortestDistances, secondPathNodeShortestDistances + MAX_NODES_COUNT, INT_MAX);

    GetShortestDistances(1, startNodeShortestDistances, destinations);
    GetShortestDistances(firstPathNode, firstPathNodeShortestDistances, destinations);
    GetShortestDistances(secondPathNode, secondPathNodeShortestDistances, destinations);

    long long shortestDistance = startNodeShortestDistances[firstPathNode] + firstPathNodeShortestDistances[secondPathNode] + secondPathNodeShortestDistances[nodesCount];
    shortestDistance = std::min(shortestDistance, startNodeShortestDistances[secondPathNode] + secondPathNodeShortestDistances[firstPathNode] + firstPathNodeShortestDistances[nodesCount]);
    
    if (shortestDistance >= INT_MAX)
    {
        std::cout << -1;
        
        return 0;
    }

    std::cout << shortestDistance;

    return 0;
}