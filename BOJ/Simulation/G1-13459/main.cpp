
#include <iostream>
#include <cassert>
#include <queue>
#include <unordered_set>
#include <string>

#define MAX_BOARD_SIZE_ROW (10)
#define MAX_BOARD_SIZE_COL (10)

#define TILT_DIRECTIONS_SIZE (4U)
#define MAX_TILT_COUNT (10U)

enum eDirection : int
{
    North = 0,
    East,
    South,
    West
};

enum eColor : int
{
    Red = 0,
    Blue
};


struct Position
{
    int Row;
    int Col;
};

struct Ball
{
    Position CurPosition;
    eColor Color;
};

struct BoardInfo
{
    std::string TransformToString()
    {
        std::string ballString = "";
        ballString.append(std::to_string(RedBall.CurPosition.Row));
        ballString.append(std::to_string(RedBall.CurPosition.Col));
        ballString.append(std::to_string(RedBall.Color));

        ballString.append(std::to_string(BlueBall.CurPosition.Row));
        ballString.append(std::to_string(BlueBall.CurPosition.Col));
        ballString.append(std::to_string(BlueBall.Color));

        return ballString;
    }

    Ball RedBall;
    Ball BlueBall;
};

const static Position TILT_DIRECTIONS[TILT_DIRECTIONS_SIZE] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static int sBoardSizeRow = 0;
static int sBoardSizeCol = 0;

bool IsPositionEqual(const Position& first, const Position& second)
{
    if (first.Row == second.Row && first.Col == second.Col)
    {
        return true;
    }

    return false;
}

int main()
{
    char board[MAX_BOARD_SIZE_ROW][MAX_BOARD_SIZE_COL] = { '.', };
    std::cin >> sBoardSizeRow >> sBoardSizeCol;

    Ball redBall;
    Ball blueBall;
    Position boardExitPosition;

    for (int row = 0; row < sBoardSizeRow; ++row)
    {
        std::string rowBoard;

        std::cin >> rowBoard;
        for (int col = 0; col < sBoardSizeCol; ++col)
        {
            board[row][col] = rowBoard[col];

            switch (board[row][col])
            {
            case 'R':
                redBall = { { row, col }, eColor::Red };

                break;
            case 'B':
                blueBall = { { row, col }, eColor::Blue };

                break;
            case 'O':
                boardExitPosition = { row, col };

                break;
            default:
                // Do nothing
                break;
            }
        }
    }

    BoardInfo startInfo = { redBall, blueBall };

    std::queue<BoardInfo> boardInfoQueue;
    boardInfoQueue.push(startInfo);

    std::string ballString = startInfo.TransformToString();

    //BoardInfo testInfo = { { { 1, 3 }, eColor::Blue }, { {3, 1}, eColor::Red } };
    //std::string testString = testInfo.TransformToString();

    std::unordered_set<std::string> visited;
    visited.insert(ballString);
    //visited.insert(testString);
    
    Position holeInPosition = { MAX_BOARD_SIZE_ROW, MAX_BOARD_SIZE_COL };

    for (unsigned int tiltCount = 0; tiltCount <= MAX_TILT_COUNT; ++tiltCount)
    {
        unsigned int boardInfoQueueSize = static_cast<unsigned int>(boardInfoQueue.size());
        for (unsigned int boardInfoCount = 0; boardInfoCount < boardInfoQueueSize; ++boardInfoCount)
        {
            BoardInfo boardInfo = boardInfoQueue.front();
            boardInfoQueue.pop();

            redBall = boardInfo.RedBall;
            blueBall = boardInfo.BlueBall;

            if (IsPositionEqual(blueBall.CurPosition, holeInPosition))
            {
                continue;
            }

            if (IsPositionEqual(redBall.CurPosition, holeInPosition))
            {
                goto complete_label;
            }

            for (unsigned int tiltDirection = 0; tiltDirection < TILT_DIRECTIONS_SIZE; ++tiltDirection)
            {
                Ball firstMoveBall;
                Ball secondMoveBall;

                switch (static_cast<eDirection>(tiltDirection))
                {
                case North:
                    if (redBall.CurPosition.Row < blueBall.CurPosition.Row)
                    {
                        firstMoveBall = redBall;
                        secondMoveBall = blueBall;
                    }
                    else
                    {
                        firstMoveBall = blueBall;
                        secondMoveBall = redBall;
                    }

                    break;
                case East:
                    if (redBall.CurPosition.Col > blueBall.CurPosition.Col)
                    {
                        firstMoveBall = redBall;
                        secondMoveBall = blueBall;
                    }
                    else
                    {
                        firstMoveBall = blueBall;
                        secondMoveBall = redBall;
                    }

                    break;
                case South:
                    if (redBall.CurPosition.Row > blueBall.CurPosition.Row)
                    {
                        firstMoveBall = redBall;
                        secondMoveBall = blueBall;
                    }
                    else
                    {
                        firstMoveBall = blueBall;
                        secondMoveBall = redBall;
                    }

                    break;
                case West:
                    if (redBall.CurPosition.Col < blueBall.CurPosition.Col)
                    {
                        firstMoveBall = redBall;
                        secondMoveBall = blueBall;
                    }
                    else
                    {
                        firstMoveBall = blueBall;
                        secondMoveBall = redBall;
                    }

                    break;
                default:
                    assert(false);
                    break;
                }

                // Todo: Need to manage visited
                // Move balls
                int moveRow = TILT_DIRECTIONS[tiltDirection].Row;
                int moveCol = TILT_DIRECTIONS[tiltDirection].Col;

                while (true)
                {
                    firstMoveBall.CurPosition.Row += moveRow;
                    firstMoveBall.CurPosition.Col += moveCol;

                    if (board[firstMoveBall.CurPosition.Row][firstMoveBall.CurPosition.Col] == '#')
                    {
                        firstMoveBall.CurPosition.Row -= moveRow;
                        firstMoveBall.CurPosition.Col -= moveCol;

                        break;
                    }

                    if (IsPositionEqual(firstMoveBall.CurPosition, boardExitPosition))
                    {
                        firstMoveBall.CurPosition.Row = MAX_BOARD_SIZE_ROW;
                        firstMoveBall.CurPosition.Col = MAX_BOARD_SIZE_COL;

                        break;
                    }
                }
                
                while (true)
                {
                    secondMoveBall.CurPosition.Row += moveRow;
                    secondMoveBall.CurPosition.Col += moveCol;

                    if (board[secondMoveBall.CurPosition.Row][secondMoveBall.CurPosition.Col] == '#' || 
                        IsPositionEqual(secondMoveBall.CurPosition, firstMoveBall.CurPosition))
                    {
                        secondMoveBall.CurPosition.Row -= moveRow;
                        secondMoveBall.CurPosition.Col -= moveCol;

                        break;
                    }

                    if (IsPositionEqual(secondMoveBall.CurPosition, boardExitPosition))
                    {
                        secondMoveBall.CurPosition.Row = MAX_BOARD_SIZE_ROW;
                        secondMoveBall.CurPosition.Col = MAX_BOARD_SIZE_COL;

                        break;
                    }
                }

                Ball newRedBall;
                Ball newBlueBall;

                if (firstMoveBall.Color == eColor::Red)
                {
                    newRedBall = firstMoveBall;
                    newBlueBall = secondMoveBall;
                }
                else
                {
                    newRedBall = secondMoveBall;
                    newBlueBall = firstMoveBall;
                }

                BoardInfo newBoardInfo = { newRedBall, newBlueBall };
                std::string newInfoString = newBoardInfo.TransformToString();

                std::pair<std::unordered_set<std::string>::iterator, bool> result = visited.insert(newInfoString);
                if (result.second == false)
                {
                    continue;
                }

                boardInfoQueue.push(newBoardInfo);
            }
        }
    }

    std::cout << '0';
    
    return 0;
    
complete_label:
    std::cout << '1';

    return 0;
}