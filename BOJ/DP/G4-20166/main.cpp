
#include <iostream>
#include <cassert>

#define MAX_MAP_SIZE (10U)
#define MAX_STRING_SIZE (6U)
#define MAX_DIRECTIONS_SIZE (8U)

struct Position
{
    int Row;
    int Col;
};

static char sCharMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

static int sMapRowSize;
static int sMapColSize;

static Position MOVE_POSITIONS[] = {
    { -1, 0 },
    { -1, 1 },
    { 0, 1 },
    { 1, 1 },
    { 1, 0 },
    { 1, -1 },
    { 0, -1 },
    { -1, -1 },
};

static unsigned int GetStringCountRecursive(const std::string& targetString, Position position, unsigned int stringIndex, unsigned int caseCounts[MAX_STRING_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    assert(stringIndex < targetString.size());

    if (sCharMap[position.Row][position.Col] != targetString[stringIndex])
    {
        return 0;
    }
    
    if (stringIndex == targetString.size() - 1)
    {
        return 1;
    }

    if (caseCounts[stringIndex][position.Row][position.Col] > 0)
    {
        return caseCounts[stringIndex][position.Row][position.Col];
    }

    unsigned int count = 0;

    for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
    {
        int nextRow = position.Row + MOVE_POSITIONS[dirIndex].Row;
        int nextCol = position.Col + MOVE_POSITIONS[dirIndex].Col;

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

        count += GetStringCountRecursive(targetString, { nextRow, nextCol }, stringIndex + 1, caseCounts);
    }

    caseCounts[stringIndex][position.Row][position.Col] = count;

    return count;
}

int main()
{
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

        unsigned int caseCounts[MAX_STRING_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
        
        unsigned int totalCount = 0;
        for (int row = 0; row < sMapRowSize; ++row)
        {
            for (int col = 0; col < sMapColSize; ++col)
            {
                unsigned int count = GetStringCountRecursive(string, { row, col }, 0, caseCounts);
                
                totalCount += count;
            }
        }

        std::cout << totalCount << '\n';
    }

    return 0;
}