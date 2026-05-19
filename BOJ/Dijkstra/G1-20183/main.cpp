
#include <climits>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_NODES_COUNT (100001U)

struct Destination
{
public:
    bool operator<(const Destination& other) const 
    {
        return AccumulatedMoney > other.AccumulatedMoney;
    }

    unsigned int Node;
    unsigned long long AccumulatedMoney;
};

static unsigned long long GetMinAccumulatedMoney(unsigned int startNode, unsigned int endNode, unsigned int shameLimit, const std::vector<Destination> destinations[])
{
    unsigned long long minAccumulatedMoneys[MAX_NODES_COUNT];
    std::fill(minAccumulatedMoneys, minAccumulatedMoneys + MAX_NODES_COUNT, ULLONG_MAX);

    minAccumulatedMoneys[startNode] = 0;

    std::priority_queue<Destination> destinationQueueAscend;
    destinationQueueAscend.push({ startNode, 0 });
    
    while (destinationQueueAscend.empty() == false)
    {
        Destination destination = destinationQueueAscend.top();
        destinationQueueAscend.pop();

        if (destination.AccumulatedMoney > minAccumulatedMoneys[destination.Node])
        {
            continue;
        }

        for (const Destination& nextDestination : destinations[destination.Node])
        {
            unsigned long long nextAccumulatedMoney = destination.AccumulatedMoney + nextDestination.AccumulatedMoney;

            if (nextAccumulatedMoney >= minAccumulatedMoneys[nextDestination.Node])
            {
                continue;
            }

            if (nextDestination.AccumulatedMoney > shameLimit)
            {
                continue;
            }

            destinationQueueAscend.push({ nextDestination.Node, nextAccumulatedMoney });
            minAccumulatedMoneys[nextDestination.Node] = nextAccumulatedMoney;
        }
    }

    return minAccumulatedMoneys[endNode];
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int nodesCount;
    unsigned int edgesCount;

    unsigned int startNode;
    unsigned int endNode;

    unsigned long long possedMoney;
    
    std::cin >> nodesCount >> edgesCount >> startNode >> endNode >> possedMoney;

    unsigned long long endShame = 0;
    std::vector<Destination> destinations[MAX_NODES_COUNT];
    for (unsigned int i = 0; i < edgesCount; ++i)
    {
        unsigned int srcNode;
        unsigned int destNode;
        unsigned long long money;

        std::cin >> srcNode >> destNode >> money;

        destinations[srcNode].push_back({ destNode, money });
        destinations[destNode].push_back({ srcNode, money });

        endShame = std::max(endShame, money);
    }

    unsigned long long minShame = ULLONG_MAX;

    unsigned long long minAccumulatedMoney = GetMinAccumulatedMoney(startNode, endNode, ULLONG_MAX, destinations);
    if (minAccumulatedMoney != ULLONG_MAX)
    {
        unsigned long long startShame = 1;

        while (startShame <= endShame)
        {
            unsigned long long checkShame = (endShame + startShame) / 2;

            minAccumulatedMoney = GetMinAccumulatedMoney(startNode, endNode, checkShame, destinations);

            if (minAccumulatedMoney <= possedMoney)
            {
                endShame = checkShame - 1;

                minShame = checkShame;
            }
            else
            {
                startShame = checkShame + 1;
            }
        }
    }

    if (minShame == ULLONG_MAX)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << minShame;
    }

    return 0;
}