
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>

#define MAX_CITIES_COUNT (1001U)

struct Destination
{
    bool operator<(const Destination& other) const
    {
        return Time > other.Time;
    }

    unsigned int City;
    unsigned int Time;
};

static void GetMinTripTimes(unsigned int startCity, unsigned int outMinTripTimes[], const std::vector<Destination> nextDestinations[])
{
    outMinTripTimes[startCity] = 0;

    std::priority_queue<Destination> destinationQueueTimeAscend;
    destinationQueueTimeAscend.push({ startCity, 0 });

    while (destinationQueueTimeAscend.empty() == false)
    {
        Destination destination = destinationQueueTimeAscend.top();
        destinationQueueTimeAscend.pop();

        if (destination.Time > outMinTripTimes[destination.City])
        {
            continue;
        }

        for (const Destination& nextDestination : nextDestinations[destination.City])
        {
            unsigned int accumulatedTime = destination.Time + nextDestination.Time;
            if (accumulatedTime >= outMinTripTimes[nextDestination.City])
            {
                continue;
            }

            outMinTripTimes[nextDestination.City] = accumulatedTime;
            destinationQueueTimeAscend.push({ nextDestination.City, accumulatedTime });
        }
    }
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int citiesCount;
    unsigned int roadsCount;
    unsigned int targetCity;

    std::cin >> citiesCount >> roadsCount >> targetCity;

    std::vector<Destination> nextDestinations[MAX_CITIES_COUNT];
    for (unsigned int i = 0; i < roadsCount; ++i)
    {
        unsigned int startCity;
        unsigned int endCity;
        unsigned int time;
        std::cin >> startCity >> endCity >> time;

        nextDestinations[startCity].push_back({ endCity , time });
    }

    unsigned int roundTripTimes[MAX_CITIES_COUNT];
    memset(roundTripTimes, UINT_MAX, sizeof(roundTripTimes));

    GetMinTripTimes(targetCity, roundTripTimes, nextDestinations);

    unsigned int maxTime = 0;
    for (unsigned int startCity = 1; startCity <= citiesCount; ++startCity)
    {
        if (startCity == targetCity)
        {
            continue;
        }

        unsigned int minTripTimes[MAX_CITIES_COUNT];
        memset(minTripTimes, UINT_MAX, sizeof(minTripTimes));

        GetMinTripTimes(startCity, minTripTimes, nextDestinations);

        roundTripTimes[startCity] += minTripTimes[targetCity];
        
        if (roundTripTimes[startCity] > maxTime)
        {
            maxTime = roundTripTimes[startCity];
        }
    }

    std::cout << maxTime;
        
    return 0;
}