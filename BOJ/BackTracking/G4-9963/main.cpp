#include <iostream>
#include <cstring>

#define MAX_BOARD_SIZE (14U)
#define MAX_MOVE_POSITIONS (3U)

struct Position
{
    int Row;
    int Col;
};

// Clockwise
static const Position MOVE_POSITIONS[MAX_MOVE_POSITIONS] =
{ 
    { 1, 1 },
    { 1, 0 }, 
    { 1, -1 }
};

static unsigned int sQueenCasesCount = 0;
static unsigned int sBoardSize = 0;
static unsigned int sMaxQueenCount = 0;

static void VisitQueenMoves(const Position& position, bool bOutVisited[MAX_BOARD_SIZE][MAX_BOARD_SIZE])
{
    bOutVisited[position.Row][position.Col] = true;

    for (unsigned int moveIndex = 0; moveIndex < MAX_MOVE_POSITIONS; ++moveIndex)
    {
        int row = position.Row;
        int col = position.Col;

        while (true)
        {
            int nextRow = row + MOVE_POSITIONS[moveIndex].Row;
            int nextCol = col + MOVE_POSITIONS[moveIndex].Col;

            if (nextRow < 0 || nextRow >= sBoardSize || nextCol < 0 || nextCol >= sBoardSize)
            {
                break;
            }

            bOutVisited[nextRow][nextCol] = true;

            row = nextRow;
            col = nextCol;
        }
    }
}

static void GetQueenCasesCountRecursive(unsigned int queenCount, const Position& position, bool bVisited[MAX_BOARD_SIZE][MAX_BOARD_SIZE])
{
    if (queenCount == sMaxQueenCount)
    {
        ++sQueenCasesCount;

        return;
    }

    for (int col = 0; col < sBoardSize; ++col)
    {
        if (bVisited[position.Row][col])
        {
            continue;
        }

        bool bCopiedVisited[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
        memcpy(bCopiedVisited, bVisited, sizeof(bCopiedVisited));

        VisitQueenMoves({ position.Row, col }, bCopiedVisited);
        GetQueenCasesCountRecursive(queenCount + 1, { position.Row + 1, col }, bCopiedVisited);
    }
}

int main()
{
    std::cin >> sBoardSize;
    sMaxQueenCount = sBoardSize;

    bool bVisited[MAX_BOARD_SIZE][MAX_BOARD_SIZE] = { false, };
    GetQueenCasesCountRecursive(0, { 0, 0 }, bVisited);

    std::cout << sQueenCasesCount;

    return 0;
}