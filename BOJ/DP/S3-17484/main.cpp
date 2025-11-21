
#include <algorithm>
#include <iostream>
#include <cassert>
#include <climits>

#define MOVE_DIRECTIONS_SIZE (3U)
#define MAX_MAP_SIZE (6U)

static int MOVE_DIRECTIONS[3][2] = {{1, -1}, {1, 0}, {1, 1}}; // SW, S, SE

int main()
{
    unsigned int map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

    int mapSizeRow = 0;
    int mapSizeCol = 0;

    std::cin >> mapSizeRow >> mapSizeCol;
    for (int row = 0; row < mapSizeRow; ++row)
    {
        for (int col = 0; col < mapSizeCol; ++col)
        {
            std::cin >> map[row][col];
            assert(map[row][col] <= 100);
        }
    }
    
    unsigned int minfuelUsedAmounts[MAX_MAP_SIZE][MAX_MAP_SIZE][MOVE_DIRECTIONS_SIZE];

    for (int row = 0; row < mapSizeRow; ++row)
    {
        for (int col = 0; col < mapSizeCol; ++col)
        {
            minfuelUsedAmounts[row][col][0] = UINT_MAX;
            minfuelUsedAmounts[row][col][1] = UINT_MAX;
            minfuelUsedAmounts[row][col][2] = UINT_MAX;
        }
    }

    for (int col = 0; col < mapSizeCol; ++col)
    {
        minfuelUsedAmounts[0][col][0] = map[0][col];
        minfuelUsedAmounts[0][col][1] = map[0][col];
        minfuelUsedAmounts[0][col][2] = map[0][col];
    }

    for (int row = 0; row < mapSizeRow - 1; ++row)
    {
        for (int col = 0; col < mapSizeCol; ++col)
        {
            for (unsigned int dirIndex = 0; dirIndex < MOVE_DIRECTIONS_SIZE; ++dirIndex)
            {
                int nextRow = row + MOVE_DIRECTIONS[dirIndex][0];
                int nextCol = col + MOVE_DIRECTIONS[dirIndex][1];

                if (nextRow < 0 || nextRow >= mapSizeRow ||
                    nextCol < 0 || nextCol >= mapSizeCol)
                {
                    continue;
                }

                minfuelUsedAmounts[nextRow][nextCol][dirIndex] =
                    std::min(minfuelUsedAmounts[row][col][(dirIndex + 1) % MOVE_DIRECTIONS_SIZE], minfuelUsedAmounts[row][col][(dirIndex + 2) % MOVE_DIRECTIONS_SIZE])
                    + map[nextRow][nextCol];
            }
        }
    }

    unsigned int minFuelAmount = UINT_MAX;
    
    int lastRow = mapSizeRow - 1;
    for (int col = 0; col < mapSizeCol; ++col)
    {
        for (unsigned int dirIndex = 0; dirIndex < MOVE_DIRECTIONS_SIZE; ++dirIndex)
        {
            unsigned int fuelAmount = minfuelUsedAmounts[lastRow][col][dirIndex];
            minFuelAmount = (fuelAmount < minFuelAmount) ? fuelAmount : minFuelAmount;
        }
    }

    std::cout << minFuelAmount;


    return 0;
}