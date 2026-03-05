#include <iostream>
#include <unordered_set>

#define MAX_MAP_SIZE (20U)
#define MAX_ALPHABETS_COUNT (26U)

static int sRowSize;
static int sColSize;

static char sMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
static bool sbVisited[MAX_ALPHABETS_COUNT] = { false, };
static unsigned int sMaxPathCount = 0;

#define MAX_DIRECTIONS_COUNT (4U)

static const std::pair<int, int> MOVE_DIRECTIONS[] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static void GetMaxPathCountRecursive(int row, int col, unsigned int pathCount)
{
    if (pathCount > sMaxPathCount)
    {
        sMaxPathCount = pathCount;
    }

    for (unsigned int moveIndex = 0; moveIndex < MAX_DIRECTIONS_COUNT; ++moveIndex)
    {
        int nextRow = row + MOVE_DIRECTIONS[moveIndex].first;
        int nextCol = col + MOVE_DIRECTIONS[moveIndex].second;

        if (nextRow < 0 || nextRow >= sRowSize || nextCol < 0 || nextCol >= sColSize)
        {
            continue;
        }

        unsigned int nextAlphabetIndex = sMap[nextRow][nextCol] - 'A';
        if (sbVisited[nextAlphabetIndex])
        {
            continue;
        }

        sbVisited[nextAlphabetIndex] = true;

        GetMaxPathCountRecursive(nextRow, nextCol, pathCount + 1);

        sbVisited[nextAlphabetIndex] = false;
    }
}

int main()
{
    std::cin >> sRowSize >> sColSize;
    for (int row = 0; row < sRowSize; ++row)
    {
        std::string rowString;
        std::cin >> rowString;

        for (int col = 0; col < sColSize; ++col)
        {
            sMap[row][col] = rowString[col];
        }
    }

    sbVisited[sMap[0][0] - 'A'] = true;
    GetMaxPathCountRecursive(0, 0, 1);

    std::cout << sMaxPathCount;

    return 0;
}