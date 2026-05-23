
#include <cstring>
#include <iostream>
#include <string>

#define MAX_MAP_SIZE (101U)
#define MAX_TARGET_SIZE (81U)

#define MAX_DIRECTIONS_COUNT (4U)

struct Position
{
    int Row;
    int Col;
};

static Position NEXT_DIRECTIONS[MAX_DIRECTIONS_COUNT] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static char sMap[MAX_MAP_SIZE][MAX_MAP_SIZE];

static int sMapRowSize;
static int sMapColSize;
static int sMoveCount;

static std::string sTargetPath;

static int maxPathCounts[MAX_TARGET_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE];

static int GetMaxPathCountRecursive(unsigned int targetIndex, int row, int col)
{
    if (targetIndex == sTargetPath.size())
    {
        return 1;
    }

    if (maxPathCounts[targetIndex][row][col] != -1)
    {
        return maxPathCounts[targetIndex][row][col];
    }

    int totalPathCount = 0;
    for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_COUNT; ++dirIndex)
    {
        for (int move = 1; move <= sMoveCount; ++move)
        {
            int nextRow = row + NEXT_DIRECTIONS[dirIndex].Row * move;
            int nextCol = col + NEXT_DIRECTIONS[dirIndex].Col * move;

            if (nextRow < 0 || nextRow >= sMapRowSize || nextCol < 0 || nextCol >= sMapColSize)
            {
                continue;
            }

            if (sMap[nextRow][nextCol] != sTargetPath[targetIndex])
            {
                continue;
            }

            totalPathCount += GetMaxPathCountRecursive(targetIndex + 1, nextRow, nextCol);
        }
    }

    maxPathCounts[targetIndex][row][col] = totalPathCount;

    return totalPathCount;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    std::cin >> sMapRowSize >> sMapColSize >> sMoveCount;

    for (int row = 0; row < sMapRowSize; ++row)
    {
        std::string mapRowString;
        std::cin >> mapRowString;

        for (int col = 0; col < sMapColSize; ++col)
        {
            sMap[row][col] = mapRowString[col];
        }
    }

    std::cin >> sTargetPath;
    
    memset(maxPathCounts, -1, sizeof(maxPathCounts));

    int totalPathCount = 0;
    for (int row = 0; row < sMapRowSize; ++row)
    {
        for (int col = 0; col < sMapColSize; ++col)
        {
            if (sMap[row][col] != sTargetPath[0])
            {
                continue;
            }

            totalPathCount += GetMaxPathCountRecursive(1, row, col);
        }
    }

    std::cout << totalPathCount;

    return 0;
}