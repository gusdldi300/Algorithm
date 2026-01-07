
#include <iostream>
#include <vector>

#define MAX_TIME (1001U)
#define MAX_MOVE_COUNT (31U)
#define MAX_POSITIONS (2U)

static std::vector<unsigned int> sFruitFallPositions;
static unsigned int sMaxFruitCounts[MAX_POSITIONS][MAX_MOVE_COUNT][MAX_TIME] = { 0, };

static unsigned int sTargetTime;
static unsigned int sMaxMoveCount;

static unsigned int GetMaxFruitsRecursive(unsigned int position, unsigned int moveCount, unsigned int time)
{
    if (time == sTargetTime)
    {
        return 0;
    }

    if (sMaxFruitCounts[position][moveCount][time] > 0)
    {
        return sMaxFruitCounts[position][moveCount][time];
    }

    unsigned int fruits = 0;
    unsigned int temp = 0;

    if (position != sFruitFallPositions[time] && moveCount < sMaxMoveCount)
    {
        fruits = GetMaxFruitsRecursive((position + 1) % 2, moveCount + 1, time + 1) + 1;
    }

    temp = GetMaxFruitsRecursive(position, moveCount, time + 1);
    if (position == sFruitFallPositions[time])
    {
        temp += 1;
    }

    fruits = std::max(fruits, temp);
    sMaxFruitCounts[position][moveCount][time] = fruits;
    
    return fruits;
}

int main()
{
    std::cin >> sTargetTime >> sMaxMoveCount;

    for (unsigned int i = 0; i < sTargetTime; ++i)
    {
        unsigned int fallPosition;
        std::cin >> fallPosition;

        fallPosition--;
        sFruitFallPositions.push_back(fallPosition);
    }

    unsigned int maxFruits = GetMaxFruitsRecursive(0, 0, 0);
    std::cout << maxFruits;

    return 0;
}