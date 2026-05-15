
#include <algorithm>
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>

#define MAX_CITIES_COUNT (100001U)

struct Destination
{
public:
    bool operator<(const Destination& other) const
    {
        return AccumulatedDistance > other.AccumulatedDistance;
    }

    unsigned int City;
    unsigned long long AccumulatedDistance;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int citiesCount;
    unsigned int edgesCount;
    unsigned int targetsCount;

    std::cin >> citiesCount >> edgesCount >> targetsCount;

    std::vector<Destination> transposedMap[MAX_CITIES_COUNT];
    for (unsigned int i = 0; i < edgesCount; ++i)
    {
        unsigned int startCity;
        unsigned int endCity;
        unsigned long long distance;

        std::cin >> startCity >> endCity >> distance; 
        transposedMap[endCity].push_back({ startCity, distance });
    }

    unsigned long long minAccumulatedDistances[MAX_CITIES_COUNT];
    std::fill(minAccumulatedDistances, minAccumulatedDistances + MAX_CITIES_COUNT, ULLONG_MAX);
    std::priority_queue<Destination> destinationQueueDistanceAscend;

    for (unsigned int i = 0; i < targetsCount; ++i)
    {
        unsigned int target;
        std::cin >> target;

        destinationQueueDistanceAscend.push({ target, 0 });
        minAccumulatedDistances[target] = 0;
    }

    while (destinationQueueDistanceAscend.empty() == false)
    {
        Destination destination = destinationQueueDistanceAscend.top();
        destinationQueueDistanceAscend.pop();

        if (destination.AccumulatedDistance > minAccumulatedDistances[destination.City])
        {
            continue;
        }

        for (const Destination& nextDestination : transposedMap[destination.City])
        {
            unsigned long long nextAccumulatedDistance = destination.AccumulatedDistance + nextDestination.AccumulatedDistance;

            if (nextAccumulatedDistance >= minAccumulatedDistances[nextDestination.City])
            {
                continue;
            }

            destinationQueueDistanceAscend.push({ nextDestination.City, nextAccumulatedDistance });
            minAccumulatedDistances[nextDestination.City] = nextAccumulatedDistance;
        }
    }

    unsigned long long maxDistanceCity = 0;
    unsigned long long maxDistance = 0;
    for (unsigned int city = 1; city <= citiesCount; ++city)
    {
        if (minAccumulatedDistances[city] > maxDistance)
        {
            maxDistanceCity = city;
            maxDistance = minAccumulatedDistances[city];
        }
    }

    std::cout << maxDistanceCity << '\n' << maxDistance;

    return 0;
}