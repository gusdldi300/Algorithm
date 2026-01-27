
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <cassert>

#define MAX_MOVE_DIRECTIONS_COUNT (4U)
#define MAX_MAP_SIZE (5)

struct Position
{
    int Row;
    int Col;
};

// N, E, S, W
static const Position MOVE_DIRECTIONS[MAX_MOVE_DIRECTIONS_COUNT] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
static std::vector<Position> sStatuePositions;

static unsigned int sMinMoveCount = UINT_MAX;

static unsigned int GetPositionMask(const Position& position)
{
    return 1 << ((position.Row * MAX_MAP_SIZE) + position.Col);
}

static bool HasVisited(const Position& position, unsigned int visitedMasks)
{
    unsigned int mask = GetPositionMask(position);

    return (visitedMasks & mask) > 0 ? true : false;
}

static void SetVisited(const Position& position, unsigned int* outVisitedMasks)
{
    unsigned int mask = GetPositionMask(position);

    (*outVisitedMasks) |= mask;
}

static void UnsetVisited(const Position& position, unsigned int* outVisitedMasks)
{
    unsigned int mask = GetPositionMask(position);

    (*outVisitedMasks) &= ~mask;
}

static bool IsStatuesAllAttached(const Position& startPosition, unsigned int statueMasks)
{

    std::queue<Position> positionQueue;
    positionQueue.push(startPosition);

    unsigned int visitedMasks = 0;
    SetVisited(startPosition, &visitedMasks);

    unsigned int attachedStatuesCount = 1;

    while (positionQueue.empty() == false)
    {
        const Position position = positionQueue.front();
        positionQueue.pop();

        for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS_COUNT; ++dirIndex)
        {
            Position nextPosition;
            nextPosition.Row = position.Row + MOVE_DIRECTIONS[dirIndex].Row;
            nextPosition.Col = position.Col + MOVE_DIRECTIONS[dirIndex].Col;

            if (nextPosition.Row < 0 || nextPosition.Row >= MAX_MAP_SIZE ||
                nextPosition.Col < 0 || nextPosition.Col >= MAX_MAP_SIZE)
            {
                continue;
            }

            if (HasVisited(nextPosition, statueMasks) == false)
            {
                continue;
            }

            if (HasVisited(nextPosition, visitedMasks))
            {
                continue;
            }

            SetVisited(nextPosition, &visitedMasks);
            positionQueue.push(nextPosition);

            attachedStatuesCount++;
        }
    }

    return (attachedStatuesCount == sStatuePositions.size()) ? true : false;
}

static void GetMinMoveCountRecursive(unsigned int statueIndex, unsigned int statueMasks, unsigned int moveSum, const Position& statuePosition)
{
    if (statueIndex == sStatuePositions.size())
    {
        if (IsStatuesAllAttached(statuePosition, statueMasks))
        {
            sMinMoveCount = std::min(sMinMoveCount, moveSum);
        }

        return;
    }

    unsigned int totalMoveCount = 0;
    unsigned int moveCount = 0;

    const Position& startPosition = sStatuePositions[statueIndex];

    std::queue<Position> positionQueue;
    positionQueue.push(startPosition);

    unsigned int visitedMasks = 0;
    SetVisited(startPosition, &visitedMasks);

    while (positionQueue.empty() == false)
    {
        unsigned int queueSize = positionQueue.size();
        for (unsigned int i = 0; i < queueSize; ++i)
        {
            const Position position = positionQueue.front();
            positionQueue.pop();

            unsigned int nextStatueMasks = statueMasks;
            SetVisited(position, &nextStatueMasks);

            GetMinMoveCountRecursive(statueIndex + 1, nextStatueMasks, moveSum + moveCount, position);

            for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS_COUNT; ++dirIndex)
            {
                Position nextPosition;
                nextPosition.Row = position.Row + MOVE_DIRECTIONS[dirIndex].Row;
                nextPosition.Col = position.Col + MOVE_DIRECTIONS[dirIndex].Col;

                if (nextPosition.Row < 0 || nextPosition.Row >= MAX_MAP_SIZE ||
                    nextPosition.Col < 0 || nextPosition.Col >= MAX_MAP_SIZE)
                {
                    continue;
                }

                if (HasVisited(nextPosition, visitedMasks))
                {
                    continue;
                }
                
                SetVisited(nextPosition, &visitedMasks);
                positionQueue.push(nextPosition);
            }
        }

        ++moveCount;
    }
}

int main()
{
    for (int row = 0; row < MAX_MAP_SIZE; ++row)
    {
        std::string rowString;
        std::cin >> rowString;

        for (int col = 0; col < MAX_MAP_SIZE; ++col)
        {
            if (rowString[col] == '*')
            {
                sStatuePositions.push_back({ row, col });
            }
        }
    }

    /*
    unsigned int visitedMasks = 0;
    for (int row = 0; row < MAX_MAP_SIZE; ++row)
    {
        for (int col = 0; col < MAX_MAP_SIZE; ++col)
        {
            assert(HasVisited({ row, col }, visitedMasks) == false);
        }
    }

    for (int row = 0; row < MAX_MAP_SIZE; ++row)
    {
        for (int col = 0; col < MAX_MAP_SIZE; ++col)
        {
            SetVisited({ row, col }, &visitedMasks);

            assert(HasVisited({ row, col }, visitedMasks));
        }
    }
    */

    GetMinMoveCountRecursive(0, 0, 0, sStatuePositions[0]);
    std::cout << sMinMoveCount;

    return 0;
}