
#include <iostream>
#include <cassert>
#include <climits>
#include <unordered_set>
#include <map>

#define MAX_MAP_SIZE (1000U)

#define MAX_BLOCK_ATTACHED_POSITIONS_SIZE (6U)
#define MAX_BLOCK_COUNT (10000U)

#define MAX_MOVE_DIRECTION_INDEXES_SIZE (7U)
#define MAX_SOURCES_SIZE (5U)

enum class Direction
{
    North,
    NorthEast,
    SouthEast,
    South,
    SouthWest,
    NorthWest
};

struct Position
{
    int Row;
    int Col;
};

// N, NE, SE, S, SW, NW
static Position BLOCK_ATTACHED_POSITIONS[MAX_BLOCK_ATTACHED_POSITIONS_SIZE] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 1 },
    { 1, 0 },
    { 0, -1 },
    { -1, -1 }
};

static Direction MOVE_DIRECTION_INDEXES[MAX_MOVE_DIRECTION_INDEXES_SIZE] =
{
    Direction::NorthWest,
    Direction::SouthWest,
    Direction::South,
    Direction::SouthEast,
    Direction::NorthEast,

    Direction::NorthEast,
    Direction::North,
};

static unsigned int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
static unsigned int sSourceCounts[MAX_SOURCES_SIZE + 1] = { 0, };
static unsigned int sBlockSources[MAX_BLOCK_COUNT + 1] = { 0, };

static void UpdateMap(const Position& position, unsigned int blockCount)
{
    std::unordered_set<unsigned int> neighborSources;
    neighborSources.reserve(MAX_SOURCES_SIZE);

    for (unsigned int attachedIndex = 0; attachedIndex < MAX_BLOCK_ATTACHED_POSITIONS_SIZE; ++attachedIndex)
    {
        int nextRow = position.Row + BLOCK_ATTACHED_POSITIONS[attachedIndex].Row;
        int nextCol = position.Col + BLOCK_ATTACHED_POSITIONS[attachedIndex].Col;

        if (sMap[nextRow][nextCol] <= 0)
        {
            continue;
        }

        neighborSources.insert(sMap[nextRow][nextCol]);
    }

    unsigned int newSource = 1;
    unsigned int minSourceCount = UINT_MAX;
    for (unsigned int source = 1; source <= MAX_SOURCES_SIZE; ++source)
    {
        if (neighborSources.find(source) != neighborSources.end())
        {
            continue;
        }

        if (sSourceCounts[source] < minSourceCount)
        {
            minSourceCount = sSourceCounts[source];
            newSource = source;
        }
    }

    sBlockSources[blockCount] = newSource;
    sMap[position.Row][position.Col] = newSource;
    sSourceCounts[newSource]++;
}

int main()
{
    // Create map
    Position position = { MAX_MAP_SIZE / 2 - 1, MAX_MAP_SIZE / 2 - 1 };
    sMap[position.Row][position.Col] = 1;
    sSourceCounts[1] = 1;
    sBlockSources[1] = 1;

    position.Row += BLOCK_ATTACHED_POSITIONS[static_cast<unsigned int>(Direction::NorthEast)].Row;
    position.Col += BLOCK_ATTACHED_POSITIONS[static_cast<unsigned int>(Direction::NorthEast)].Col;
    UpdateMap(position, 2);

    unsigned int blockCount = 3;
    unsigned int maxMoveCount = 1;

    while (blockCount <= MAX_BLOCK_COUNT)
    {
        for (unsigned int movesIndex = 0; movesIndex < MAX_MOVE_DIRECTION_INDEXES_SIZE; ++movesIndex)
        {
            unsigned int moveCount = maxMoveCount;

            if (movesIndex == 5)
            {
                moveCount = 1;
            }

            Direction moveDirection = MOVE_DIRECTION_INDEXES[movesIndex];
            while (moveCount > 0)
            {
                position.Row += BLOCK_ATTACHED_POSITIONS[static_cast<unsigned int>(moveDirection)].Row;
                position.Col += BLOCK_ATTACHED_POSITIONS[static_cast<unsigned int>(moveDirection)].Col;

                UpdateMap(position, blockCount);
                ++blockCount;

                --moveCount;
            }
        }

        maxMoveCount++;
    }

    unsigned int testCount;
    std::cin >> testCount;

    std::map<unsigned int, unsigned int> targetNumbers;

    for (unsigned int i = 0; i < testCount; ++i)
    {
        unsigned int targetNumber;
        std::cin >> targetNumber;

        std::cout << sBlockSources[targetNumber] << std::endl;
    }

    return 0;
}