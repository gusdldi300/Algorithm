
#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <cassert>

#define MAX_BLOCK_COUNT (10000U)
#define MAX_BOUNDARY_ROW_COUNT (2U)

#define MAX_BOARD_SIZE_ROW (6U)
#define MAX_BOARD_SIZE_COL (4U)

#define BLOCK_TYPE_SIZE (3U)
#define MAX_DIRECTIONS_SIZE (4U)

#define DIRECTION_SOUTH_INDEX (2U)
#define MAX_BLOCK_SIZE (2U)

struct Position
{
    int Row;
    int Col;
};

struct Block
{
    int StartRow;
    int StartCol;

    unsigned int Type;
};

static Position MOVE_DIRECTIONS[MAX_DIRECTIONS_SIZE] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static unsigned int sGreenBoard[MAX_BOARD_SIZE_ROW][MAX_BOARD_SIZE_COL] = { false, };
static unsigned int sBlueBoard[MAX_BOARD_SIZE_ROW][MAX_BOARD_SIZE_COL] = { false, };

static std::vector<Position> sBlockTypesInfo[BLOCK_TYPE_SIZE];
static unsigned int sScore = 0;

static void PrintBoard(const unsigned int board[][MAX_BOARD_SIZE_COL])
{
    for (int row = 0; row < MAX_BOARD_SIZE_ROW; ++row)
    {
        for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
        {
            std::cout << board[row][col] << ' ';
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}

static unsigned int GetRemainedBlocksCount(const unsigned int board[][MAX_BOARD_SIZE_COL])
{
    unsigned int count = 0;
    for (int row = 0; row < MAX_BOARD_SIZE_ROW; ++row)
    {
        for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
        {
            if (board[row][col] > 0)
            {
                count++;
            }
        }
    }

    return count;
}

static bool GetFloatingBlock(std::vector<Position>& outFoundBlock, const unsigned int board[][MAX_BOARD_SIZE_COL])
{
    std::queue<unsigned int> floatingBlockIds;
    bool bVisited[MAX_BOARD_SIZE_ROW][MAX_BOARD_SIZE_COL] = { false, };

    for (int row = MAX_BOARD_SIZE_ROW - 1; row >= 0; --row)
    {
        for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
        {
            if (board[row][col] == 0 || bVisited[row][col])
            {
                continue;
            }

            bool bFloatingBlock = true;

            std::queue<Position> positions;
            positions.push({ row, col });
            bVisited[row][col] = true;

            while (positions.empty() == false)
            {
                Position position = positions.front();
                positions.pop();

                outFoundBlock.push_back(position);

                int buttomRow = position.Row + 1;
                unsigned int blockId = board[position.Row][position.Col];

                if (buttomRow == MAX_BOARD_SIZE_ROW ||
                    (board[buttomRow][position.Col] != 0 && board[buttomRow][position.Col] != blockId))
                {
                    bFloatingBlock = false;
                }

                for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
                {
                    int nextRow = position.Row + MOVE_DIRECTIONS[dirIndex].Row;
                    int nextCol = position.Col + MOVE_DIRECTIONS[dirIndex].Col;

                    if (nextRow < 0 || nextRow >= MAX_BOARD_SIZE_ROW ||
                        nextCol < 0 || nextCol >= MAX_BOARD_SIZE_COL)
                    {
                        continue;
                    }

                    if (bVisited[nextRow][nextCol] || board[nextRow][nextCol] != blockId)
                    {
                        continue;
                    }

                    bVisited[nextRow][nextCol] = true;
                    positions.push({ nextRow, nextCol });
                }
            }

            if (bFloatingBlock)
            {
                // Move block
                return true;
            }

            outFoundBlock.clear();
        }
    }

    return false;
}

static void StartGame(unsigned int board[][MAX_BOARD_SIZE_COL], const Block& block, unsigned int blockCount)
{
    // Move blocks
    int nextRow = 0;
    bool bCrashed = false;

    for (nextRow = 1; nextRow < MAX_BOARD_SIZE_ROW; ++nextRow)
    {
        for (Position& position : sBlockTypesInfo[block.Type])
        {
            if (board[nextRow][block.StartCol + position.Col] > 0)
            {
                goto MOVE_LABEL;
            }
        }
    }

MOVE_LABEL:
    for (Position& position : sBlockTypesInfo[block.Type])
    {
        board[nextRow + position.Row - 1][block.StartCol + position.Col] = blockCount;
    }

    // PrintBoard(board);

    while (true)
    {
        // Remove full row
        bool bFullHandled = false;

        for (int row = 0; row < MAX_BOARD_SIZE_ROW; ++row)
        {
            bool bFull = true;
            for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
            {
                if (board[row][col] == 0)
                {
                    bFull = false;
                    break;
                }
            }

            if (bFull)
            {
                for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
                {
                    board[row][col] = 0;
                }

                ++sScore;
                bFullHandled = true;
            }
        }

        if (bFullHandled == false)
        {
            break;
        }

        // Move floating clusters
        while (true)
        {
            std::vector<Position> floatingBlock;
            if (GetFloatingBlock(floatingBlock, board) == false)
            {
                break;
            }

            // Move floating block
            unsigned int blockId = board[floatingBlock[0].Row][floatingBlock[0].Col];
            unsigned int minMoveCount = UINT_MAX;
            for (Position& position : floatingBlock)
            {
                int buttomRow = position.Row + 1;
                assert(buttomRow < MAX_BOARD_SIZE_ROW);

                if (board[buttomRow][position.Col] == blockId)
                {
                    continue;
                }

                while (true)
                {
                    if (buttomRow == MAX_BOARD_SIZE_ROW || board[buttomRow][position.Col] != 0)
                    {
                        break;
                    }

                    ++buttomRow;
                }

                unsigned int moveCount = (buttomRow - 1) - position.Row;
                minMoveCount = (moveCount < minMoveCount ? moveCount : minMoveCount);
            }

            for (Position& position : floatingBlock)
            {
                board[position.Row][position.Col] = 0;
                board[position.Row + minMoveCount][position.Col] = blockId;
            }
        }
    }

    //PrintBoard(board);

    // Handle boundaries 
    bool bBlockFound = false;

    int boundaryRow = 0;
    for (boundaryRow = 0; boundaryRow < MAX_BOUNDARY_ROW_COUNT; ++boundaryRow)
    {
        for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
        {
            if (board[boundaryRow][col] > 0)
            {
                bBlockFound = true;

                goto BOUNDARY_BLOCK_FOUND_LABEL;
            }
        }
    }

BOUNDARY_BLOCK_FOUND_LABEL:
    if (bBlockFound)
    {
        int moveCount = MAX_BOUNDARY_ROW_COUNT - boundaryRow;

        for (int row = MAX_BOARD_SIZE_ROW - 1; row >= MAX_BOUNDARY_ROW_COUNT; --row)
        {
            for (int col = 0; col < MAX_BOARD_SIZE_COL; ++col)
            {
                board[row][col] = board[row - moveCount][col];
                board[row - moveCount][col] = 0;
            }
        }
    }

    //PrintBoard(board);
}

int main()
{
    sBlockTypesInfo[0].push_back({ 0, 0 });

    sBlockTypesInfo[1].push_back({ 0, 0 });
    sBlockTypesInfo[1].push_back({ 0, 1 });

    sBlockTypesInfo[2].push_back({ 0, 0 });
    sBlockTypesInfo[2].push_back({ -1, 0 });

    unsigned int blockCount = 0;
    std::cin >> blockCount;

    for (unsigned int blockId = 1; blockId <= blockCount; ++blockId)
    {
        Block greenBlock;
        
        std::cin >> greenBlock.Type >> greenBlock.StartRow >> greenBlock.StartCol;
        greenBlock.Type--;

        Block blueBlock;
        blueBlock.StartRow = greenBlock.StartCol;
        blueBlock.StartCol = (MAX_BOARD_SIZE_COL - 1) - greenBlock.StartRow;

        switch (greenBlock.Type)
        {
        case 0:
            blueBlock.Type = greenBlock.Type;

            break;

        case 1:
            blueBlock.Type = 2;

            break;
            
        case 2:
            blueBlock.Type = 1;
            blueBlock.StartCol--;

            break;

        default:
            assert(false);
            break;
        }

        StartGame(sGreenBoard, greenBlock, blockId);
        StartGame(sBlueBoard, blueBlock, blockId);

        continue;
    }

    std::cout << sScore << std::endl << (GetRemainedBlocksCount(sGreenBoard) + GetRemainedBlocksCount(sBlueBoard));

    return 0;
}
