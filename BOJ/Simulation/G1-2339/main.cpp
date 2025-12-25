
#include <iostream>
#include <vector>
#include <queue>

#define MAX_SLATE_SIZE (20U)
#define MAX_MOVE_POSITIONS (4U)

enum class Direction : unsigned int
{
    North = 0,
    East,
    South,
    West
};

enum class CutDirection
{
    Horizon,
    Vertical
};

struct Position
{
    int Row;
    int Col;
};

static Position MOVE_POSITIONS[MAX_MOVE_POSITIONS] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static int sSlateSize;

static bool IsPositionOnBound(int row, int col)
{
    if (row < 0 || row >= sSlateSize || col < 0 || col >= sSlateSize)
    {
        return false;
    }

    return true;
}

static bool hasJewelOn(const Position& startPosition, const Direction direction, const unsigned int slate[][MAX_SLATE_SIZE])
{
    int nextRow = startPosition.Row;
    int nextCol = startPosition.Col;

    while (true)
    {
        nextRow += MOVE_POSITIONS[static_cast<unsigned int>(direction)].Row;
        nextCol += MOVE_POSITIONS[static_cast<unsigned int>(direction)].Col;

        if (IsPositionOnBound(nextRow, nextCol) == false || slate[nextRow][nextCol] == 3)
        {
            break;
        }

        if (slate[nextRow][nextCol] == 2)
        {
            return true;
        }
    }

    return false;
}

static void DrawLineOn(const Position& startPosition, const Direction direction, unsigned int slate[][MAX_SLATE_SIZE])
{
    int nextRow = startPosition.Row;
    int nextCol = startPosition.Col;

    while (true)
    {
        slate[nextRow][nextCol] = 3;

        nextRow += MOVE_POSITIONS[static_cast<unsigned int>(direction)].Row;
        nextCol += MOVE_POSITIONS[static_cast<unsigned int>(direction)].Col;
        
        if (IsPositionOnBound(nextRow, nextCol) == false || slate[nextRow][nextCol] == 3)
        {
            break;
        }
    }
}

static bool DrawLine(const Position& startPosition, const CutDirection cutDirection, unsigned int slate[][MAX_SLATE_SIZE])
{
    Direction firstDirection;
    Direction secondDirection;

    if (cutDirection == CutDirection::Horizon)
    {
        firstDirection = Direction::West;
        secondDirection = Direction::East;
    }
    else
    {
        firstDirection = Direction::North;
        secondDirection = Direction::South;
    }

    if (hasJewelOn(startPosition, firstDirection, slate) || hasJewelOn(startPosition, secondDirection, slate))
    {
        return false;
    }

    DrawLineOn(startPosition, firstDirection, slate);
    DrawLineOn(startPosition, secondDirection, slate);

    return true;
}

// Returns 
static void GetSubSlateInformations(std::vector<Position>* outImpurities, unsigned int* outJewelsCount, const Position& startPosition, const unsigned int slate[][MAX_SLATE_SIZE])
{
    bool visited[MAX_SLATE_SIZE][MAX_SLATE_SIZE] = { false, };
    
    std::queue<Position> positionQueue;
    positionQueue.push(startPosition);
    visited[startPosition.Row][startPosition.Col] = true;

    while (positionQueue.empty() == false)
    {
        Position position = positionQueue.front();
        positionQueue.pop();

        if (slate[position.Row][position.Col] == 1)
        {
            outImpurities->push_back(position);
        }
        else if (slate[position.Row][position.Col] == 2)
        {
            (*outJewelsCount)++;
        }

        for (unsigned int moveIndex = 0; moveIndex < MAX_MOVE_POSITIONS; ++moveIndex)
        {
            int nextRow = position.Row + MOVE_POSITIONS[static_cast<unsigned int>(moveIndex)].Row;
            int nextCol = position.Col + MOVE_POSITIONS[static_cast<unsigned int>(moveIndex)].Col;

            if (IsPositionOnBound(nextRow, nextCol) == false)
            {
                continue;
            }

            if (slate[nextRow][nextCol] == 3 || visited[nextRow][nextCol])
            {
                continue;
            }

            visited[nextRow][nextCol] = true;
            positionQueue.push({ nextRow, nextCol });
        }
    }

}

static void CopySlate(unsigned int outSlate[][MAX_SLATE_SIZE], const unsigned int slate[][MAX_SLATE_SIZE])
{
    for (unsigned int row = 0; row < sSlateSize; ++row)
    {
        for (unsigned int col = 0; col < sSlateSize; ++col)
        {
            outSlate[row][col] = slate[row][col];
        }
    }
}

static int GetJewelMakeCasesRecursive(const Position& impurity, const CutDirection cutDirection, const unsigned int slate[][MAX_SLATE_SIZE])
{
    unsigned int copiedSlate[MAX_SLATE_SIZE][MAX_SLATE_SIZE];
    CopySlate(copiedSlate, slate);
    
    if (DrawLine(impurity, cutDirection, copiedSlate) == false)
    {
        return 0;
    }

    std::vector<Direction> searchDirections;
    
    CutDirection nextCutDirection;
    if (cutDirection == CutDirection::Horizon)
    {
        searchDirections.push_back(Direction::North);
        searchDirections.push_back(Direction::South);

        nextCutDirection = CutDirection::Vertical;
    }
    else
    {
        searchDirections.push_back(Direction::East);
        searchDirections.push_back(Direction::West);

        nextCutDirection = CutDirection::Horizon;
    }
    
    unsigned int jewelCaseCount = 1;

    for (Direction searchDirection : searchDirections)
    {
        unsigned int caseCount = 0;

        Position startPosition;
        startPosition.Row = impurity.Row + MOVE_POSITIONS[static_cast<unsigned int>(searchDirection)].Row;
        startPosition.Col = impurity.Col + MOVE_POSITIONS[static_cast<unsigned int>(searchDirection)].Col;

        std::vector<Position> nextImpurities;
        unsigned int jewelsCount = 0;

        GetSubSlateInformations(&nextImpurities, &jewelsCount, startPosition, copiedSlate);
        if (nextImpurities.size() == (jewelsCount - 1))
        {
            if (jewelsCount == 1)
            {
                caseCount = 1;
            }
            else
            {
                for (const Position& nextImpurity : nextImpurities)
                {
                    caseCount += GetJewelMakeCasesRecursive(nextImpurity, nextCutDirection, copiedSlate);
                }
            }
        }
        
        jewelCaseCount *= caseCount;
    }

    return jewelCaseCount;
}

int main()
{
    unsigned int slate[MAX_SLATE_SIZE][MAX_SLATE_SIZE];

    std::cin >> sSlateSize;

    std::vector<Position> impurities;
    std::vector<Position> jewels;

    for (int row = 0; row < sSlateSize; ++row)
    {
        for (int col = 0; col < sSlateSize; ++col)
        {
            unsigned int source;
            std::cin >> source;

            slate[row][col] = source;

            if (source == 1)
            {
                impurities.push_back({ row, col });
            }
            else if (source == 2)
            {
                jewels.push_back({ row, col });
            }
        }
    }
    
    unsigned int jewelCaseCount = 0;
    for (const Position& impurity : impurities)
    {
        jewelCaseCount += GetJewelMakeCasesRecursive(impurity, CutDirection::Horizon, slate);
        jewelCaseCount += GetJewelMakeCasesRecursive(impurity, CutDirection::Vertical, slate);
    }
    
    if (jewelCaseCount == 0)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << jewelCaseCount;
    }

    return 0;
}