#include <iostream>
#include <cstring>

#define MAX_MAP_SIZE (501U)
#define MAX_DIRECTIONS_COUNT (4U)

static int sMapSize;
static int sMoveCounts[MAX_MAP_SIZE][MAX_MAP_SIZE];
static unsigned int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

static const std::pair<int, int> MOVE_DIRECTIONS[MAX_DIRECTIONS_COUNT] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static unsigned int GetMoveCountRecursive(int row, int col)
{
    if (sMoveCounts[row][col] >= 0)
    {
        return sMoveCounts[row][col];
    }

    unsigned int moveCount = 0;
    for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_COUNT; ++dirIndex)
    {
        int nextRow = row + MOVE_DIRECTIONS[dirIndex].first;
        int nextCol = col + MOVE_DIRECTIONS[dirIndex].second;

        if (nextRow < 0 || nextRow >= sMapSize || nextCol < 0 || nextCol >= sMapSize)
        {
            continue;
        }

        if (sMap[nextRow][nextCol] <= sMap[row][col])
        {
            continue;
        }

        moveCount = std::max(moveCount, GetMoveCountRecursive(nextRow, nextCol) + 1);
    }

    sMoveCounts[row][col] = moveCount;
    return moveCount;
}

int main()
{
    std::cin >> sMapSize;
    for (int row = 0; row < sMapSize; ++row)
    {
        for (int col = 0; col < sMapSize; ++col)
        {
            std::cin >> sMap[row][col];
        }
    }

    memset(sMoveCounts, -1, sizeof(sMoveCounts));
    unsigned int maxMoveCount = 0;
    for (int row = 0; row < sMapSize; ++row)
    {
        for (int col = 0; col < sMapSize; ++col)
        {
            maxMoveCount = std::max(maxMoveCount, GetMoveCountRecursive(row, col));
        }
    }

    std::cout << maxMoveCount + 1;

    return 0;
}