
#include <algorithm>
#include <iostream>
#include <cstring>

#define MAX_MAP_SIZE (501)
#define MAX_DIRECTIONS_COUNT (4)

static const std::pair<int, int> MOVE_POSITIONS[MAX_DIRECTIONS_COUNT] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static int sMapSize;
static int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
static int sMaxMoveCounts[MAX_MAP_SIZE][MAX_MAP_SIZE];

static int GetMaxMoveCountRecursive(int row, int col)
{
    if (sMaxMoveCounts[row][col] >= 0)
    {
        return sMaxMoveCounts[row][col];
    }

    int moveCount = 1;
    for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_COUNT; ++dirIndex)
    {
        int nextRow = row + MOVE_POSITIONS[dirIndex].first;
        int nextCol = col + MOVE_POSITIONS[dirIndex].second;

        if (nextRow < 0 || nextRow >= MAX_MAP_SIZE ||
            nextCol < 0 || nextCol >= MAX_MAP_SIZE)
        {
            continue;
        }

        if (sMap[row][col] >= sMap[nextRow][nextCol])
        {
            continue;
        }

        int nextMoveCounts = GetMaxMoveCountRecursive(nextRow, nextCol) + 1;
        moveCount = std::max(moveCount, nextMoveCounts);
    }

    sMaxMoveCounts[row][col] = moveCount;

    return moveCount;
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cin >> sMapSize;
    for (int row = 0; row < sMapSize; ++row)
    {
        for (int col = 0; col < sMapSize; ++col)
        {
            std::cin >> sMap[row][col];
        }
    }

    memset(sMaxMoveCounts, -1, sizeof(sMaxMoveCounts));

    int maxMoveCount = 0;
    for (int row = 0; row < sMapSize; ++row)
    {
        for (int col = 0; col < sMapSize; ++col)
        {
            maxMoveCount = std::max(maxMoveCount, GetMaxMoveCountRecursive(row, col));
        }
    }

    std::cout << maxMoveCount;

    return 0;
}