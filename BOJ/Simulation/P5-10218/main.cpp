
#include <iostream>
#include <queue>
#include <cassert>

#define MAX_MAZE_SIZE (10U)
#define MAX_MOVE_COUNT (11U)
#define MAX_MOVE_DIRECTIONS (4U)

struct Position
{
    int Row;
    int Col;
};

static const Position MOVE_DIRECTIONS[MAX_MOVE_DIRECTIONS] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } }; // U, R, D, L
static const char DIRECTIONS[MAX_MOVE_DIRECTIONS] = { 'U', 'R', 'D', 'L' };

static std::string sExitPaths;

static void GetMinExitPathsRecursive(unsigned int moveCount, std::string& lastPaths, const std::queue<Position>& lastStartPositions, const char maze[][MAX_MAZE_SIZE])
{
    if (moveCount == MAX_MOVE_COUNT)
    {
        return;
    }

    if (lastStartPositions.empty())
    {
        if (lastPaths.size() < sExitPaths.size())
        {
            sExitPaths = lastPaths;
        }

        return;
    }

    char lastPath = lastPaths[lastPaths.size() - 1];

    for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS; ++dirIndex)
    {
        char moveDirection = DIRECTIONS[dirIndex];

        if (lastPath == 'U' || lastPath == 'D')
        {
            if (moveDirection == 'U' || moveDirection == 'D')
            {
                continue;
            }
        }
        else if (lastPath == 'L' || lastPath == 'R')
        {
            if (moveDirection == 'L' || moveDirection == 'R')
            {
                continue;
            }
        }

        std::queue<Position> startPositions = lastStartPositions;
        unsigned int positionsSize = startPositions.size();

        for (unsigned int i = 0; i < positionsSize; ++i)
        {
            Position position = startPositions.front();
            startPositions.pop();

            int curRow = position.Row;
            int curCol = position.Col;

            while (true)
            {
                int nextRow = curRow + MOVE_DIRECTIONS[dirIndex].Row;
                int nextCol = curCol + MOVE_DIRECTIONS[dirIndex].Col;

                if (maze[nextRow][nextCol] == '#')
                {
                    startPositions.push({ curRow, curCol });
                 
                    break;
                }

                if (maze[nextRow][nextCol] == 'O')
                {
                    break;
                }

                curRow = nextRow;
                curCol = nextCol;
            }
        }

        lastPaths.push_back(moveDirection);
        GetMinExitPathsRecursive(moveCount + 1, lastPaths, startPositions, maze);
        lastPaths.pop_back();
    }
}

int main()
{
    unsigned int testsCount;
    std::cin >> testsCount;

    for (unsigned int test = 0; test < testsCount; ++test)
    {
        int mazeSizeRow;
        int mazeSizeCol;
        
        std::cin >> mazeSizeRow >> mazeSizeCol;
        
        char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
        
        std::queue<Position> startPositions;
        for (int row = 0; row < mazeSizeRow; ++row)
        {
            std::string rowMazeString;
            std::cin >> rowMazeString;

            for (int col = 0; col < mazeSizeCol; ++col)
            {
                maze[row][col] = rowMazeString[col];

                if (maze[row][col] == '.')
                {
                    startPositions.push({ row, col });
                }
            }
        }

        sExitPaths = "INIT_EXIT_PATHS"; 
        
        std::string paths = "S";
        GetMinExitPathsRecursive(0, paths, startPositions, maze);

        if (sExitPaths.size() > MAX_MOVE_COUNT)
        {
            std::cout << "XHAE" << std::endl;
        }
        else
        {
            std::cout << (sExitPaths.c_str() + 1) << std::endl;
        }
    }

    return 0;
}