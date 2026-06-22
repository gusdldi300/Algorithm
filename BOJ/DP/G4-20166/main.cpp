
#include <cstring>
#include <iostream>
#include <cassert>

#define MAX_MAP_SIZE (10U)
#define MAX_STRING_SIZE (6U)
#define MAX_MOVES_SIZE (8U)

struct Position
{
    int Row;
    int Col;
};

static char sCharMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

static int sMapRowSize;
static int sMapColSize;

static Position MOVE_POSITIONS[MAX_MOVES_SIZE] = {
    { -1, 0 },
    { -1, 1 },
    { 0, 1 },
    { 1, 1 },
    { 1, 0 },
    { 1, -1 },
    { 0, -1 },
    { -1, -1 },
};

int GetTargetStringCasesCountRercursive(Position position, unsigned int stringIndex, const std::string& targetString, int targetStringCasesCount[MAX_STRING_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    if (stringIndex == targetString.size())
    {
        return 1;
    }
    
    int totalCasesCount = 0;
    for (unsigned int moveIndex = 0; moveIndex < MAX_MOVES_SIZE; ++moveIndex)
    {
        int nextRow = position.Row + MOVE_POSITIONS[moveIndex].Row;
        int nextCol = position.Col + MOVE_POSITIONS[moveIndex].Col;

        if (nextRow < 0)
        {
            nextRow = sMapRowSize - 1;
        }
        else if (nextRow >= sMapRowSize)
        {
            nextRow = 0;
        }

        if (nextCol < 0)
        {
            nextCol = sMapColSize - 1;
        }
        else if (nextCol >= sMapColSize)
        {
            nextCol = 0;
        }

        if (sCharMap[nextRow][nextCol] != targetString[stringIndex])
        {
            continue;
        }

        if (targetStringCasesCount[stringIndex + 1][nextRow][nextCol] != -1)
        {
            totalCasesCount += targetStringCasesCount[stringIndex + 1][nextRow][nextCol];

            continue;
        }

        totalCasesCount += GetTargetStringCasesCountRercursive({ nextRow, nextCol }, stringIndex + 1, targetString, targetStringCasesCount);
    }

    targetStringCasesCount[stringIndex][position.Row][position.Col] = totalCasesCount;
    
    return totalCasesCount;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int stringsCount;
    std::cin >> sMapRowSize >> sMapColSize >> stringsCount;
    
    for (int row = 0; row < sMapRowSize; ++row)
    {
        std::string mapRowString;
        std::cin >> mapRowString;

        for (int col = 0; col < sMapColSize; ++col)
        {
            sCharMap[row][col] = mapRowString[col];
        }
    }

    for (unsigned int i = 0; i < stringsCount; ++i)
    {
        std::string string;
        std::cin >> string;

        int targetStringCasesCount[MAX_STRING_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE];
        memset(targetStringCasesCount, -1, sizeof(targetStringCasesCount));

        int totalCasesCount = 0;
        for (int row = 0; row < sMapRowSize; ++row)
        {
            for (int col = 0; col < sMapColSize; ++col)
            {
                if (sCharMap[row][col] != string[0])
                {
                    continue;
                }

                totalCasesCount += GetTargetStringCasesCountRercursive({ row, col }, 1, string, targetStringCasesCount);
            }
        }

        std::cout << totalCasesCount << '\n';
    }

    return 0;
}