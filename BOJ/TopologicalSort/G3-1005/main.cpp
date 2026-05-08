
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

#define MAX_BUILDINGS_COUNT (1001U)

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        unsigned int buildingsCount;
        unsigned int sequencesCount;
        std::cin >> buildingsCount >> sequencesCount;

        unsigned int requiredBuildTimes[MAX_BUILDINGS_COUNT] = { 0, };
        for (unsigned int building = 1; building <= buildingsCount; ++building)
        {
            unsigned int time;
            std::cin >> time;

            requiredBuildTimes[building] = time;
        }

        std::vector<unsigned int> nextBuildingLists[MAX_BUILDINGS_COUNT];
        unsigned int lastBuildingsCount[MAX_BUILDINGS_COUNT] = { 0, };
        for (unsigned int j = 0; j < sequencesCount; ++j)
        {
            unsigned int lastBuilding;
            unsigned int building;
            
            std::cin >> lastBuilding >> building;

            nextBuildingLists[lastBuilding].push_back(building);
            ++lastBuildingsCount[building];
        }

        std::vector<unsigned int> startBuildings;
        for (unsigned int building = 1; building <= buildingsCount; ++building)
        {
            if (lastBuildingsCount[building] == 0)
            {
                startBuildings.push_back(building);
            }
        }

        std::queue<unsigned int> buildingQueue; 
        unsigned int accumulatedMinBuidTimes[MAX_BUILDINGS_COUNT] = { 0, };

        for (unsigned int startBuilding : startBuildings)
        {
            buildingQueue.push(startBuilding);
            accumulatedMinBuidTimes[startBuilding] = requiredBuildTimes[startBuilding];
        }
        
        while (buildingQueue.empty() == false)
        {
            unsigned int building = buildingQueue.front();
            buildingQueue.pop();

            for (unsigned int nextBuilding : nextBuildingLists[building])
            {
                accumulatedMinBuidTimes[nextBuilding] = std::max(accumulatedMinBuidTimes[nextBuilding], accumulatedMinBuidTimes[building]);

                --lastBuildingsCount[nextBuilding];

                if (lastBuildingsCount[nextBuilding] == 0)
                {
                    accumulatedMinBuidTimes[nextBuilding] += requiredBuildTimes[nextBuilding];
                    
                    buildingQueue.push(nextBuilding);
                }
            }
        }

        unsigned int targetBuilding;
        std::cin >> targetBuilding;

        std::cout << accumulatedMinBuidTimes[targetBuilding] << '\n';
    }

    return 0;
}