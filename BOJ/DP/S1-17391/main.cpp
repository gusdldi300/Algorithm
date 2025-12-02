
#include <algorithm>
#include <iostream>
#include <climits>

#define MAX_MAP_SIZE (300U)

static unsigned int sPathCounts[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

int main()
{
    unsigned int mapSizeRow = 0;
    unsigned int mapSizeCol = 0;

    std::cin >> mapSizeRow >> mapSizeCol;

    for (unsigned int row = 0; row < mapSizeRow; ++row)
    {
        for (unsigned int col = 0; col < mapSizeCol; ++col)
        {
            sPathCounts[row][col] = UINT_MAX;
        }
    }

    sPathCounts[0][0] = 0;
    for (unsigned int row = 0; row < mapSizeRow; ++row)
    {
        for (unsigned int col = 0; col < mapSizeCol; ++col)
        {
            unsigned int itemCount = 0;
            std::cin >> itemCount;

            if (sPathCounts[row][col] == UINT_MAX)
            {
                continue;
            }

            for (unsigned int item = 1; item <= itemCount; ++item)
            {
                unsigned int nextRow = row + item;
                if (nextRow < mapSizeRow)
                {
                    sPathCounts[nextRow][col] = std::min(sPathCounts[nextRow][col], sPathCounts[row][col] + 1);
                }

                unsigned int nextCol = col + item;
                if (nextCol < mapSizeCol)
                {
                    sPathCounts[row][nextCol] = std::min(sPathCounts[row][nextCol], sPathCounts[row][col] + 1);
                }
            }
        }
    }

    std::cout << sPathCounts[mapSizeRow - 1][mapSizeCol - 1];

    return 0;
}