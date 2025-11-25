
#include <iostream>

#define MAX_MAP_SIZE (300U)

static unsigned int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
static unsigned int sMinerals[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

int main()
{
    unsigned int mapSizeRow = 0;
    unsigned int mapSizeCol = 0;

    std::cin >> mapSizeRow >> mapSizeCol;

    for (unsigned int row = 0; row < mapSizeRow; ++row)
    {
        for (unsigned int col = 0; col < mapSizeCol; ++col)
        {
            std::cin >> sMap[row][col];
        }
    }
    
    sMinerals[0][0] = sMap[0][0];
    for (unsigned int row = 0; row < mapSizeRow; ++row)
    {
        for (unsigned int col = 0; col < mapSizeCol; ++col)
        {
            unsigned int nextCol = col + 1;
            if (nextCol < mapSizeCol)
            {
                sMinerals[row][nextCol] = std::max(sMinerals[row][nextCol], sMinerals[row][col] + sMap[row][nextCol]);
            }

            unsigned int nextRow = row + 1;
            if (nextRow < mapSizeRow)
            {
                sMinerals[nextRow][col] = std::max(sMinerals[nextRow][col], sMinerals[row][col] + sMap[nextRow][col]);
            }

        }
    }

    std::cout << sMinerals[mapSizeRow - 1][mapSizeCol - 1];

    return 0;
}