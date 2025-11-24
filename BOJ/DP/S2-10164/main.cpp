
#include <iostream>
#include <queue>

#define MAX_BOARD_SIZE (15U)
#define MAX_DIRECTIONS_SIZE (2U)

struct Position
{
    int Row;
    int Col;
};

static const Position MOVE_DIRECTIONS[MAX_DIRECTIONS_SIZE] = { { 0, 1 }, { 1, 0 } };

static unsigned int sPaths[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { 0, };
static int sBoardSizeRow = 0;
static int sBoardSizeCol = 0;

static void SetPaths(const Position& startPosition, const Position& exitPosition)
{
    std::queue<Position> positions;
    positions.push({ startPosition.Row, startPosition.Col });

    while (positions.empty() == false)
    {
        Position position = positions.front();
        positions.pop();

        for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
        {
            Position nextPosition = { position.Row + MOVE_DIRECTIONS[dirIndex].Row,
                position.Col + MOVE_DIRECTIONS[dirIndex].Col };

            if (nextPosition.Row < 0 || nextPosition.Row > exitPosition.Row ||
                nextPosition.Col < 0 || nextPosition.Col > exitPosition.Col)
            {
                continue;
            }

            if (sPaths[nextPosition.Row][nextPosition.Col] == 0)
            {
                positions.push(nextPosition);
            }

            sPaths[nextPosition.Row][nextPosition.Col] += sPaths[position.Row][position.Col];
        }
    }
}

int main()
{
    std::cin >> sBoardSizeRow >> sBoardSizeCol;
    
    int mustPassNumber;
    std::cin >> mustPassNumber;
    mustPassNumber--;

    Position startPosition = { 0, 0 };
    Position exitPosition = { sBoardSizeRow - 1, sBoardSizeCol - 1};

    sPaths[0][0] = 1;

    Position mustPassPosition = startPosition;
    if (mustPassNumber >= 0)
    {
        mustPassPosition.Row = mustPassNumber / sBoardSizeCol;
        mustPassPosition.Col = mustPassNumber % sBoardSizeCol;

        SetPaths(startPosition, mustPassPosition);
    }

    SetPaths(mustPassPosition, exitPosition);

    std::cout << sPaths[sBoardSizeRow - 1][sBoardSizeCol - 1];

    return 0;
}
