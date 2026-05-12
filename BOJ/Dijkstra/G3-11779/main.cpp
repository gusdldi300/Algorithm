
#include <cstring>
#include <climits>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>

#define MAX_CITIES_COUNT (1001U)

struct Destination
{
    unsigned int City;
    unsigned int Cost;

    bool operator<(const Destination& other) const
    {
        return Cost > other.Cost;
    }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int citiesCount;
    std::cin >> citiesCount;

    unsigned int busesCount;
    std::cin >> busesCount;

    std::vector<Destination> destinations[MAX_CITIES_COUNT];

    unsigned int startCity;
    unsigned int endCity;
    for (unsigned int i = 0; i < busesCount; ++i)
    {
        unsigned int cost;

        std::cin >> startCity >> endCity >> cost;
        destinations[startCity].push_back({ endCity, cost });
    }

    std::cin >> startCity >> endCity;
    
    unsigned int accumulatedCosts[MAX_CITIES_COUNT];
    memset(accumulatedCosts, UINT_MAX, sizeof(accumulatedCosts));

    unsigned int prevCity[MAX_CITIES_COUNT] = { 0, };
    std::priority_queue<Destination> destinationQueueAscend;

    destinationQueueAscend.push({ startCity, 0 });
    accumulatedCosts[startCity] = 0;

    while (destinationQueueAscend.empty() == false)
    {
        Destination destination = destinationQueueAscend.top();
        destinationQueueAscend.pop();

        if (destination.Cost > accumulatedCosts[destination.City])
        {
            continue;
        }

        for (const Destination& nextDestination : destinations[destination.City])
        {
            unsigned int nextCost = destination.Cost + nextDestination.Cost;
            if (nextCost >= accumulatedCosts[nextDestination.City])
            {
                continue;
            }

            prevCity[nextDestination.City] = destination.City;
            accumulatedCosts[nextDestination.City] = nextCost;
            destinationQueueAscend.push({ nextDestination.City, nextCost });
        }
    }

    std::cout << accumulatedCosts[endCity] << '\n';

    std::stack<unsigned int> pathStack;
    unsigned int city = endCity;
    while (city != 0)
    {
        pathStack.push(city);

        city = prevCity[city];
    }

    std::cout << pathStack.size() << '\n';
    while (pathStack.empty() == false)
    {
        std::cout << pathStack.top() << ' ';
        pathStack.pop();
    }

    return 0;
}