#include <iostream>

#define MAX_MAP_SIZE (500U)
#define MAX_MOVE_DIRECTIONS (4U)

static int sRowSize;
static int sColSize;

static unsigned int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
static unsigned int sPathCounts[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
static bool sbVisited[MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };

static const std::pair<int, int> MOVE_DIRECTIONS[] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static unsigned int GetMovePathsCountRecursive(int row, int col)
{
    if (row == (sRowSize - 1) && col == (sColSize - 1))
    {
        return 1;
    }

    unsigned int height = sMap[row][col];

    unsigned int totalPathCount = 0;
    for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS; ++dirIndex)
    {
        int nextRow = row + MOVE_DIRECTIONS[dirIndex].first;
        int nextCol = col + MOVE_DIRECTIONS[dirIndex].second;

        if (nextRow < 0 || nextRow >= sRowSize || nextCol < 0 || nextCol >= sColSize)
        {
            continue;
        }

        if (sMap[nextRow][nextCol] >= height)
        {
            continue;
        }

        if (sbVisited[nextRow][nextCol])
        {
            totalPathCount += sPathCounts[nextRow][nextCol];

            continue;
        }

        unsigned int pathCount = GetMovePathsCountRecursive(nextRow, nextCol);
        totalPathCount += pathCount;
    }

    sbVisited[row][col] = true;
    sPathCounts[row][col] = totalPathCount;

    return totalPathCount;
}

int main()
{
    std::cin >> sRowSize >> sColSize;

    for (int row = 0; row < sRowSize; ++row)
    {
        for (int col = 0; col < sColSize; ++col)
        {
            unsigned int height;
            std::cin >> height;

            sMap[row][col] = height;
        }
    }

    std::cout << GetMovePathsCountRecursive(0, 0);
    
    return 0;
}