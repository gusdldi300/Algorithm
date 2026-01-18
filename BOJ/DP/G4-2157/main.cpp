
#include <iostream>
#include <vector>

#define MAX_CITIES_COUNT (301U)
#define MIN_VISITED_COUNT (2U)
#define MAX_VISITED_COUNT (MAX_CITIES_COUNT)

struct AirLine
{
    unsigned int DepartCity;
    unsigned int Score;
};

static unsigned int sMaxScores[MAX_CITIES_COUNT][MAX_VISITED_COUNT] = { 0, };
std::vector<AirLine> sAirLines[MAX_CITIES_COUNT];

int main()
{
    unsigned int citiesCount;
    unsigned int maxVisitedCount;
    unsigned int airLinesCount;

    std::cin >> citiesCount >> maxVisitedCount >> airLinesCount;

    for (unsigned int i = 0; i < airLinesCount; ++i)
    {
        AirLine airLine;
        std::cin >> airLine.DepartCity;

        unsigned int arriveCity;
        std::cin >> arriveCity >> airLine.Score;

        if (airLine.DepartCity >= arriveCity)
        {
            continue;
        }

        if (airLine.DepartCity == 1)
        {
            sMaxScores[arriveCity][MIN_VISITED_COUNT] = std::max(sMaxScores[arriveCity][MIN_VISITED_COUNT], airLine.Score);
        }

        sAirLines[arriveCity].push_back(std::move(airLine));
    }

    for (unsigned int arriveCity = 2; arriveCity <= citiesCount; ++arriveCity)
    {
        for (unsigned int visitedCount = MIN_VISITED_COUNT + 1; visitedCount <= maxVisitedCount; ++visitedCount)
        {
            for (const AirLine& airLine : sAirLines[arriveCity])
            {
                if (airLine.DepartCity < arriveCity && sMaxScores[airLine.DepartCity][visitedCount - 1] > 0)
                {
                    sMaxScores[arriveCity][visitedCount] = std::max(sMaxScores[arriveCity][visitedCount],
                                                                    sMaxScores[airLine.DepartCity][visitedCount - 1] + airLine.Score);
                }
            }
        }
    }

    unsigned int maxScore = 0;
    for (unsigned int visitedCount = MIN_VISITED_COUNT; visitedCount <= maxVisitedCount; ++visitedCount)
    {
        maxScore = std::max(maxScore, sMaxScores[citiesCount][visitedCount]);
    }

    std::cout << maxScore;

    return 0;
}