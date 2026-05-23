
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
#include <queue>

#define MAX_NODES_COUNT (100001U)

struct Destination
{
public:
    bool operator<(const Destination& other) const
    {
        return StartTime > other.StartTime;
    }
    
    unsigned int Node;
    long long StartTime;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int nodesCount;
    long long period;

    std::cin >> nodesCount >> period;

    std::vector<Destination> destinations[MAX_NODES_COUNT];
    for (unsigned int startTime = 0; startTime < period; ++startTime)
    {
        unsigned int startNode;
        unsigned int endNode;

        std::cin >> startNode >> endNode;

        destinations[startNode].push_back({ endNode, startTime });
        destinations[endNode].push_back({ startNode, startTime });
    }

    long long minTimes[MAX_NODES_COUNT];
    std::fill(minTimes, minTimes + MAX_NODES_COUNT, LLONG_MAX);

    std::priority_queue<Destination> destinationQueueAscend;
    destinationQueueAscend.push({ 1, 0 });
    minTimes[1] = 0;

    while (destinationQueueAscend.empty() == false)
    {
        Destination destination = destinationQueueAscend.top();
        destinationQueueAscend.pop();

        if (destination.StartTime > minTimes[destination.Node])
        {
            continue;
        }

        for (const Destination& nextDestination : destinations[destination.Node])
        {   
            long long tick = destination.StartTime / period;
            long long nextStartTime = nextDestination.StartTime + (tick * period);
            if (nextStartTime < destination.StartTime)
            {
                nextStartTime += period;
            }

            ++nextStartTime;

            if (nextStartTime >= minTimes[nextDestination.Node])
            {
                continue;
            }

            minTimes[nextDestination.Node] = nextStartTime;
            destinationQueueAscend.push({ nextDestination.Node, nextStartTime });
        }
    }

    std::cout << minTimes[nodesCount];

    return 0;
}