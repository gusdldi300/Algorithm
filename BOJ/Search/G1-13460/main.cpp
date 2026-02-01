#include <iostream>
#include <queue>
#include <cassert>

#define MAX_SHIFT_COUNT (10U)
#define MAX_MAP_SIZE (10U)
#define MAX_DIRECTIONS_SIZE (4U)

#define HOLE_IN (-1)

enum class Direction : unsigned int
{
    Up,
    Right,
    Down,
    Left
};

struct Position
{
    int Row;
    int Col;
};

struct BallsInfo
{
    Position RedPosition;
    Position BluePosition;
};

struct MoveInfo
{
    Direction MoveDirection;
    Position MovePosition;
};

static MoveInfo MOVE_INFOS[MAX_DIRECTIONS_SIZE] = { 
    { Direction::Up, { -1, 0, } }, 
    { Direction::Right, { 0, 1 } },
    { Direction::Down, { 1, 0 } },
    { Direction::Left, { 0, -1 } },
};

inline static void SetVisited(const BallsInfo& ballsInfo, bool outbVisited[MAX_MAP_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    outbVisited[ballsInfo.RedPosition.Row][ballsInfo.RedPosition.Col][ballsInfo.BluePosition.Row][ballsInfo.BluePosition.Col] = true;
}

inline static bool HasVisited(const BallsInfo& ballsInfo, const bool bVisited[MAX_MAP_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    return bVisited[ballsInfo.RedPosition.Row][ballsInfo.RedPosition.Col][ballsInfo.BluePosition.Row][ballsInfo.BluePosition.Col];
}

inline static void SwapPositionPointer(Position** outppFirst, Position** outppSecond)
{
    Position* pTemp = *outppFirst;
    *outppFirst = *outppSecond;
    *outppSecond = pTemp;
}

inline static void MoveBall(Position* outBallPosition, const Position& otherBallPosition, const MoveInfo& moveInfo, const char map[][MAX_MAP_SIZE])
{
    Position nextPosition = *outBallPosition;

    while (true)
    {
        nextPosition.Row += (moveInfo.MovePosition.Row);
        nextPosition.Col += (moveInfo.MovePosition.Col);

        if ((map[nextPosition.Row][nextPosition.Col] == '#') || 
            (nextPosition.Row == otherBallPosition.Row && nextPosition.Col == otherBallPosition.Col))
        {
            nextPosition.Row -= (moveInfo.MovePosition.Row);
            nextPosition.Col -= (moveInfo.MovePosition.Col);

            break;
        }

        if (map[nextPosition.Row][nextPosition.Col] == 'O')
        {
            nextPosition = { -1, -1 };

            break;
        }
    }

    *outBallPosition = nextPosition;
}

int main()
{
    static int sMapRowSize;
    static int sMapColSize;

    std::cin >> sMapRowSize >> sMapColSize;

    char map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

    BallsInfo ballsInfo;

    for (int row = 0; row < sMapRowSize; ++row)
    {
        std::string mapRow;
        std::cin >> mapRow;

        for (int col = 0; col < sMapColSize; ++col)
        {
            if (mapRow[col] == 'B')
            {
                ballsInfo.BluePosition = { row, col };
            }
            else if (mapRow[col] == 'R')
            {
                ballsInfo.RedPosition = { row, col };
            }
            else
            {
                map[row][col] = mapRow[col];
            }
        }
    }
    
    // Set red, blue
    bool bVisited[MAX_MAP_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };

    std::queue<BallsInfo> ballsInfoQueue;
    ballsInfoQueue.push(ballsInfo);
    SetVisited(ballsInfo, bVisited);

    bool bHoleIn = false;
    unsigned int shiftCount = 0;
    while (ballsInfoQueue.empty() == false)
    {
        if (shiftCount >= MAX_SHIFT_COUNT)
        {
            break;
        }

        unsigned int queueSize = ballsInfoQueue.size();
        for (unsigned int i = 0; i < queueSize; ++i)
        {
            BallsInfo ballsInfo = ballsInfoQueue.front();
            ballsInfoQueue.pop();

            for (MoveInfo moveInfo : MOVE_INFOS)
            {
                BallsInfo nextBallsInfo = ballsInfo;

                // Decide first move ball
                Position* pFirstMoveBall = &nextBallsInfo.RedPosition;
                Position* pSecondMoveBall = &nextBallsInfo.BluePosition;

                switch (moveInfo.MoveDirection)
                {
                case Direction::Up:
                    if (nextBallsInfo.RedPosition.Row > nextBallsInfo.BluePosition.Row)
                    {
                        SwapPositionPointer(&pFirstMoveBall, &pSecondMoveBall);
                    }

                    break;
                case Direction::Right:
                    if (nextBallsInfo.RedPosition.Col < nextBallsInfo.BluePosition.Col)
                    {
                        SwapPositionPointer(&pFirstMoveBall, &pSecondMoveBall);
                    }

                    break;
                case Direction::Down:
                    if (nextBallsInfo.RedPosition.Row < nextBallsInfo.BluePosition.Row)
                    {
                        SwapPositionPointer(&pFirstMoveBall, &pSecondMoveBall);
                    }

                    break;
                case Direction::Left:
                    if (nextBallsInfo.RedPosition.Col > nextBallsInfo.BluePosition.Col)
                    {
                        SwapPositionPointer(&pFirstMoveBall, &pSecondMoveBall);
                    }

                    break;

                default:
                    assert(false);
                }

                MoveBall(pFirstMoveBall, *pSecondMoveBall, moveInfo, map);
                MoveBall(pSecondMoveBall, *pFirstMoveBall, moveInfo, map);

                if (nextBallsInfo.BluePosition.Row == HOLE_IN)
                {
                    continue;
                }

                if (nextBallsInfo.RedPosition.Row == HOLE_IN)
                {
                    bHoleIn = true;

                    goto COMPLETE_LABEL;
                }

                if (HasVisited(nextBallsInfo, bVisited))
                {
                    continue;
                }

                SetVisited(nextBallsInfo, bVisited);
                ballsInfoQueue.push(nextBallsInfo);
            }
        }
        
        ++shiftCount;
    }

COMPLETE_LABEL:
    if (bHoleIn)
    {
        std::cout << (shiftCount + 1);
    }
    else
    {
        std::cout << -1;
    }

    return 0;
}