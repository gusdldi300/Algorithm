
#include <algorithm>
#include <cassert>
#include <climits>
#include <queue>
#include <iostream>

#define MAX_FISH_TANK_SIZE (100U)
#define MAX_DIRECTIONS_SIZE (2U)

#define FISH_SUPPLY_DIVISOR (5U)

struct Position
{
    int Row;
    int Col;
};

static unsigned int sFishTanks[MAX_FISH_TANK_SIZE][MAX_FISH_TANK_SIZE] = { 0, };

static const Position MOVE_DIRECTIONS[MAX_DIRECTIONS_SIZE] = { { 0, 1 }, { 1, 0 } };

static void CopyFishTanks(unsigned int destTanks[][MAX_FISH_TANK_SIZE], const unsigned int srcTanks[][MAX_FISH_TANK_SIZE])
{
    for (int row = 0; row < MAX_FISH_TANK_SIZE; ++row)
    {
        for (int col = 0; col < MAX_FISH_TANK_SIZE; ++col)
        {
            destTanks[row][col] = srcTanks[row][col];
        }
    }
}

static bool DisplaceWithRotated90CWArray(const Position& rotateStart, const Position& rotateEnd, const Position& destPosition, unsigned int fishTanks[][MAX_FISH_TANK_SIZE], unsigned int fishTanksSize)
{
    unsigned int rotateSizeRow = (rotateEnd.Row - rotateStart.Row) + 1;
    if (destPosition.Col + rotateSizeRow > fishTanksSize)
    {
        return false;
    }

    int destCol = destPosition.Col;
    for (int row = rotateEnd.Row; row >= rotateStart.Row; --row)
    {
        int destRow = destPosition.Row;
        for (int col = rotateStart.Col; col <= rotateEnd.Col; ++col)
        {
            fishTanks[destRow][destCol] = fishTanks[row][col];
            fishTanks[row][col] = 0;

            ++destRow;
        }

        ++destCol;
    }

    return true;
}

static void AdjustFishCounts(unsigned int fishTanks[][MAX_FISH_TANK_SIZE])
{
    unsigned int tempTanks[MAX_FISH_TANK_SIZE][MAX_FISH_TANK_SIZE] = { 0, };
    CopyFishTanks(tempTanks, fishTanks);

    for (int row = 0; row < MAX_FISH_TANK_SIZE; ++row)
    {
        for (int col = 0; col < MAX_FISH_TANK_SIZE; ++col)
        {
            if (fishTanks[row][col] == 0)
            {
                continue;
            }

            for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
            {
                int nextRow = row + MOVE_DIRECTIONS[dirIndex].Row;
                int nextCol = col + MOVE_DIRECTIONS[dirIndex].Col;

                if (nextRow < 0 || nextRow >= MAX_FISH_TANK_SIZE ||
                    nextCol < 0 || nextCol >= MAX_FISH_TANK_SIZE)
                {
                    continue;
                }

                if (fishTanks[nextRow][nextCol] == 0)
                {
                    continue;
                }

                unsigned int supplyFishCount = fishTanks[row][col];
                if (supplyFishCount == fishTanks[nextRow][nextCol])
                {
                    continue;
                }
                else if (supplyFishCount < fishTanks[nextRow][nextCol])
                {
                    supplyFishCount = (fishTanks[nextRow][nextCol] - supplyFishCount) / FISH_SUPPLY_DIVISOR;

                    tempTanks[nextRow][nextCol] -= supplyFishCount;
                    tempTanks[row][col] += supplyFishCount;
                }
                else
                {
                    supplyFishCount = (supplyFishCount - fishTanks[nextRow][nextCol]) / FISH_SUPPLY_DIVISOR;

                    tempTanks[row][col] -= supplyFishCount;
                    tempTanks[nextRow][nextCol] += supplyFishCount;
                }
            }
        }
    }

    CopyFishTanks(fishTanks, tempTanks);
}

static void PlaceTanksOnFloor(unsigned int fishTanks[][MAX_FISH_TANK_SIZE], unsigned int fishTanksCount)
{
    int fishTanksCol = 0;

    for (int col = 0; col < fishTanksCount; ++col)
    {
        if (fishTanks[MAX_FISH_TANK_SIZE - 1][col] == 0)
        {
            continue;
        }

        int row = MAX_FISH_TANK_SIZE - 1;
        while (sFishTanks[row][col] > 0)
        {
            unsigned int moveFish = sFishTanks[row][col];

            sFishTanks[row][col] = 0;
            sFishTanks[MAX_FISH_TANK_SIZE - 1][fishTanksCol] = moveFish;

            ++fishTanksCol;
            --row;
        }
    }
}

int main()
{
    unsigned int fishTanksCount = 0;
    unsigned int targetFishCount = 0;

    std::cin >> fishTanksCount >> targetFishCount;

    for (unsigned int fishTank = 0; fishTank < fishTanksCount; ++fishTank)
    {
        std::cin >> sFishTanks[MAX_FISH_TANK_SIZE - 1][fishTank];
        assert(sFishTanks[MAX_FISH_TANK_SIZE - 1][fishTank] > 0);
    }

    unsigned int cleanCount = 0;
    while (true)
    {
        unsigned int minFishCount = UINT_MAX;
        unsigned int maxFishCount = 0;
        for (int fishTank = 0; fishTank < fishTanksCount; ++fishTank)
        {
            minFishCount = std::min(minFishCount, sFishTanks[MAX_FISH_TANK_SIZE - 1][fishTank]);
            maxFishCount = std::max(maxFishCount, sFishTanks[MAX_FISH_TANK_SIZE - 1][fishTank]);
        }
        
        if (maxFishCount - minFishCount <= targetFishCount)
        {
            break;
        }

        // Add 1 fish to minimum fish tanks
        for (int fishTank = 0; fishTank < fishTanksCount; ++fishTank)
        {
            if (sFishTanks[MAX_FISH_TANK_SIZE - 1][fishTank] == minFishCount)
            {
                sFishTanks[MAX_FISH_TANK_SIZE - 1][fishTank]++;
            }
        }

        Position start = { MAX_FISH_TANK_SIZE - 1, 0 };
        Position end = { MAX_FISH_TANK_SIZE - 1, 0 };

        int rotateSizeCol = end.Col - start.Col + 1;
        int rotateSizeRow = end.Row - start.Row + 1;

        Position dest = { MAX_FISH_TANK_SIZE - 1 - rotateSizeCol, start.Col + rotateSizeCol };

        while (DisplaceWithRotated90CWArray(start, end, dest, sFishTanks, fishTanksCount))
        {
            start = dest;
            end.Row = start.Row + rotateSizeCol;
            end.Col = start.Col + rotateSizeRow - 1;

            rotateSizeCol = end.Col - start.Col + 1;
            rotateSizeRow = end.Row - start.Row + 1;

            dest.Row = MAX_FISH_TANK_SIZE - 1 - rotateSizeCol;
            dest.Col = start.Col + rotateSizeCol;
        }

        AdjustFishCounts(sFishTanks);
        PlaceTanksOnFloor(sFishTanks, fishTanksCount);

        rotateSizeCol = fishTanksCount;
        start.Row = MAX_FISH_TANK_SIZE - 1;
        start.Col = 0;

        dest = start;

        for (rotateSizeRow = 1; rotateSizeRow <= 2; ++rotateSizeRow)
        {
            rotateSizeCol /= 2;

            dest.Row -= rotateSizeRow;
            dest.Col += rotateSizeCol;

            int rowDest = dest.Row;
            for (int row = start.Row; row > start.Row - rotateSizeRow; --row)
            {
                int colDest = dest.Col;
                for (int col = start.Col + rotateSizeCol - 1; col >= start.Col; --col)
                {
                    sFishTanks[rowDest][colDest] = sFishTanks[row][col];
                    sFishTanks[row][col] = 0;

                    ++colDest;
                }

                ++rowDest;
            }

            start.Col = dest.Col;
        }

        AdjustFishCounts(sFishTanks);
        PlaceTanksOnFloor(sFishTanks, fishTanksCount);

        ++cleanCount;
    }
    
    std::cout << cleanCount;

    return 0;
}