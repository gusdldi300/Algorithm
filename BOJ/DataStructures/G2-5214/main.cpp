#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

#define MAX_TUBES_COUNT (1001U)
#define MAX_STATIONS_COUNT (100001U)

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int stationsCount;
    unsigned int tubeEdgesCount;
    unsigned int tubesCount;

    std::cin >> stationsCount >> tubeEdgesCount >> tubesCount;

    std::vector<unsigned int> connectedTubes[MAX_STATIONS_COUNT];
    std::vector<unsigned int> connectedStations[MAX_TUBES_COUNT];
    for (unsigned int tube = 1; tube <= tubesCount; ++tube)
    {
        for (unsigned int j = 1; j <= tubeEdgesCount; ++j)
        {
            unsigned int station;
            std::cin >> station;

            connectedTubes[station].push_back(tube);
            connectedStations[tube].push_back(station);
        }
    }

    // Search shortest distance
    std::queue<unsigned int> stationQueue;
    std::unordered_set<unsigned int> visitedStations;
    std::unordered_set<unsigned int> visitedTubes;
    
    unsigned int startStation = 1;
    stationQueue.push(startStation);
    visitedStations.insert(startStation);

    bool bMovable = false;
    int visitedCount = 1;
    while (stationQueue.empty() == false)
    {
        unsigned int queueSize = stationQueue.size();

        for (unsigned int i = 0; i < queueSize; ++i)
        {
            unsigned int station = stationQueue.front();
            stationQueue.pop();

            if (station == stationsCount)
            {
                bMovable = true;

                goto FOUND_LABEL;
            }

            for (unsigned tube : connectedTubes[station])
            {
                if (visitedTubes.find(tube) != visitedTubes.end())
                {
                    continue;
                }

                visitedTubes.insert(tube);
                for (unsigned int nextStation : connectedStations[tube])
                {
                    if (visitedStations.find(nextStation) != visitedStations.end())
                    {
                        continue;
                    }

                    stationQueue.push(nextStation);
                    visitedStations.insert(nextStation);
                }
            }
        }
        
        ++visitedCount;
    }

FOUND_LABEL:

    if (bMovable == false)
    {
        visitedCount = -1;
    }

    std::cout << visitedCount;

    return 0;
}