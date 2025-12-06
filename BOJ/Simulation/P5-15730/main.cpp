
#include <algorithm>
#include <iostream>
#include <queue>

#define MAX_MOUNTAIN_SIZE (100U)
#define MAX_DIRECTIONS_SIZE (4U)

struct Position
{
    int Row;
    int Col;
};

static const Position CHECK_DIRECTIONS[MAX_DIRECTIONS_SIZE] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static unsigned int sMountain[MAX_MOUNTAIN_SIZE][MAX_MOUNTAIN_SIZE] = { 0, };

static int sMountainSizeRow = 0;
static int sMountainSizeCol = 0;

static bool IsSurrounded(const Position& startPosition, unsigned int currentHeight, bool visited[][MAX_MOUNTAIN_SIZE], std::queue<Position>* outSurroundedPositions)
{
    std::queue<Position> positions;
    positions.push(startPosition);
    visited[startPosition.Row][startPosition.Col] = true;
    
    outSurroundedPositions->push(startPosition);

    bool bSurrounded = true;
    while (positions.empty() == false)
    {
        Position position = positions.front();
        positions.pop();

        for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
        {
            int nextRow = position.Row + CHECK_DIRECTIONS[dirIndex].Row;
            int nextCol = position.Col + CHECK_DIRECTIONS[dirIndex].Col;

            if ((nextRow < 0 || nextRow >= sMountainSizeRow ||
                nextCol < 0 || nextCol >= sMountainSizeCol) || 
                currentHeight > sMountain[nextRow][nextCol])
            {
                bSurrounded = false;

                continue;
            }

            if (visited[nextRow][nextCol] || (sMountain[nextRow][nextCol] != currentHeight))
            {
                continue;
            }

            Position nextPosition = { nextRow, nextCol };

            positions.push(nextPosition);
            visited[nextRow][nextCol] = true;

            outSurroundedPositions->push(nextPosition);
        }
    }

    return bSurrounded;
}

int main()
{
    std::cin >> sMountainSizeRow >> sMountainSizeCol;

    unsigned int maxHeight = 0;
    for (unsigned int row = 0; row < sMountainSizeRow; ++row)
    {
        for (unsigned int col = 0; col < sMountainSizeCol; ++col)
        {
            unsigned int height = 0;
            std::cin >> height;

            sMountain[row][col] = height;
            maxHeight = std::max(maxHeight, height);
        }
    }

    unsigned int waterAmount = 0;
    for (unsigned int height = 0; height < maxHeight; ++height)
    {
        bool visited[MAX_MOUNTAIN_SIZE][MAX_MOUNTAIN_SIZE] = { false, };

        for (int row = 0; row < sMountainSizeRow; ++row)
        {
            for (int col = 0; col < sMountainSizeCol; ++col)
            {
                if (sMountain[row][col] != height || visited[row][col])
                {
                    continue;
                }

                // Check height;
                std::queue<Position> surroundedPositions;

                Position startPosition = { row, col };
                if (IsSurrounded(startPosition, height, visited, &surroundedPositions) == false)
                {
                    continue;
                }

                // Pour water
                waterAmount += surroundedPositions.size();

                while (surroundedPositions.empty() == false)
                {
                    Position surroundedPosition = surroundedPositions.front();
                    surroundedPositions.pop();

                    sMountain[surroundedPosition.Row][surroundedPosition.Col]++;
                }
            }
        }
    }

    std::cout << waterAmount;

    return 0;
}
