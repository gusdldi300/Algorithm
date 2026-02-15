
#include <iostream>

#define MAX_MAP_SIZE (1000U)
#define MAX_MILK_SHOP_COUNT (3U)
#define MAX_MOVE_DIRECTIONS_COUNT (2U)

struct Position
{
    int Row;
    int Col;
};

const static Position MOVE_DIRECTIONS[] = { { 0, 1 }, { 1, 0 } };

static unsigned int sMapSize;
static unsigned int sMilkMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
static unsigned int sMilkDrankCounts[MAX_MILK_SHOP_COUNT + 1][MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

unsigned int GetMaxMilkDrankCountRecurisve(unsigned int row, unsigned int col, unsigned int lastMilk)
{
    if (sMilkDrankCounts[lastMilk][row][col] > 0)
    {
        return sMilkDrankCounts[lastMilk][row][col];
    }

    unsigned int totalDrankCount = 1;
    unsigned int nextMilk = (lastMilk + 1) % MAX_MILK_SHOP_COUNT;

    if (sMilkMap[row][col] != nextMilk)
    {
        --totalDrankCount;
        nextMilk = lastMilk;
    }

    unsigned int drankCount = 0;
    for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS_COUNT; ++dirIndex)
    {
        unsigned int nextRow = row + MOVE_DIRECTIONS[dirIndex].Row;
        unsigned int nextCol = col + MOVE_DIRECTIONS[dirIndex].Col;

        if (nextRow >= sMapSize || nextCol >= sMapSize)
        {
            continue;
        }

        unsigned int tempCount = GetMaxMilkDrankCountRecurisve(nextRow, nextCol, nextMilk);
        drankCount = std::max(drankCount, tempCount);
    }
    
    totalDrankCount += drankCount;

    sMilkDrankCounts[lastMilk][row][col] = totalDrankCount;

    return totalDrankCount;
}

int main()
{
    std::cin >> sMapSize;

    
    for (unsigned int row = 0; row < sMapSize; ++row)
    {
        for (unsigned int col = 0; col < sMapSize; ++col)
        {
            std::cin >> sMilkMap[row][col];
        }
    }

    std::cout << GetMaxMilkDrankCountRecurisve(0, 0, MAX_MILK_SHOP_COUNT - 1);

    return 0;
}