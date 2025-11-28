
#include <algorithm>
#include <climits>
#include <iostream>

#define MAX_COST (1000000)

#define MAX_MAP_SIZE_ROW (100000U)
#define MAX_MAP_SIZE_COL (3U)

#define MAX_DIRECTIONS_SIZE (4U)

static int sMinCosts[MAX_MAP_SIZE_ROW][MAX_MAP_SIZE_COL] = { 0, };

static const int MOVE_DIRECTIONS[MAX_DIRECTIONS_SIZE][2] = { { 0, 1 }, { 1, -1 }, { 1, 0 }, { 1, 1 } };

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int test = 1;
    
    while (true)
    {
        unsigned int mapSizeRow = 0;
        std::cin >> mapSizeRow;

        if (mapSizeRow == 0)
        {
            break;
        }

        for (int row = 0; row < mapSizeRow; ++row)
        {
            for (int col = 0; col < MAX_MAP_SIZE_COL; ++col)
            {
                sMinCosts[row][col] = INT_MAX;
            }
        }

        std::cin >> sMinCosts[0][0];
        std::cin >> sMinCosts[0][1];
        std::cin >> sMinCosts[0][2];

        sMinCosts[0][2] += sMinCosts[0][1];

        sMinCosts[1][0] = sMinCosts[0][1];
        sMinCosts[1][1] = std::min(sMinCosts[0][1], sMinCosts[0][2]);
        sMinCosts[1][2] = sMinCosts[1][1];

        for (int row = 1; row < mapSizeRow; ++row)
        {
            for (int col = 0; col < MAX_MAP_SIZE_COL; ++col)
            {
                int cost = 0;
                std::cin >> cost;

                sMinCosts[row][col] += cost;
                
                for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
                {
                    int nextRow = row + MOVE_DIRECTIONS[dirIndex][0];
                    int nextCol = col + MOVE_DIRECTIONS[dirIndex][1];

                    if (nextRow < 0 || nextRow >= mapSizeRow ||
                        nextCol < 0 || nextCol >= MAX_MAP_SIZE_COL)
                    {
                        continue;
                    }

                    sMinCosts[nextRow][nextCol] = std::min(sMinCosts[nextRow][nextCol], sMinCosts[row][col]);
                }
            }
        }

        std::cout << test << ". " << sMinCosts[mapSizeRow - 1][1] << "\n";
        
        ++test;
    }

    return 0;
}