
#include <iostream>
#include <vector>
#include <queue>

#define MAX_MAP_SIZE (20U)
#define MAX_MOVE_DIRECTIONS (4U)

struct Position
{
    int Row;
    int Col;
};

struct Signal
{
    bool bStartEW;
    unsigned int TimeEW;
    unsigned int TimeNS;
};

static const Position MOVE_DIRECTION_POSITIONS[MAX_MOVE_DIRECTIONS] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

static bool GetMinimumArrivalTime(unsigned int* outTime, const std::vector<Signal>& signals, const char map[][MAX_MAP_SIZE], const int mapSizeRow, const int mapSizeCol, const Position& startPosition, const Position& endPosition)
{
    bool visited[MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };

    std::queue<Position> positionQueue;
    positionQueue.push(startPosition);

    visited[startPosition.Row][startPosition.Col] = true;

    unsigned int time = 0;

    while (positionQueue.empty() == false)
    {
        unsigned int queueSize = positionQueue.size();
        for (unsigned int i = 0; i < queueSize; ++i)
        {
            Position position = positionQueue.front();
            positionQueue.pop();

            if (position.Row == endPosition.Row && position.Col == endPosition.Col)
            {
                *outTime = time;

                return true;
            }

            for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS; ++dirIndex)
            {
                int nextRow = position.Row + MOVE_DIRECTION_POSITIONS[dirIndex].Row;
                int nextCol = position.Col + MOVE_DIRECTION_POSITIONS[dirIndex].Col;

                if (nextRow < 0 || nextRow >= mapSizeRow ||
                    nextCol < 0 || nextCol >= mapSizeCol)
                {
                    continue;
                }

                char mapState = map[nextRow][nextCol];
                if (mapState == '.' || visited[nextRow][nextCol])
                {
                    continue;
                }

                bool bPassedSignal = true;
                if (mapState >= '0' && mapState <= '9')
                {
                    const Signal& signal = signals[mapState - '0'];
                    unsigned int totalTime = (signal.TimeEW + signal.TimeNS);
                    unsigned int cycledTime = (time + 1) % totalTime;
                    cycledTime = (cycledTime == 0) ? totalTime : cycledTime;

                    if (signal.bStartEW)
                    {
                        if (cycledTime <= signal.TimeEW)
                        {
                            if (dirIndex == 0 || dirIndex == 2)
                            {
                                bPassedSignal = false;
                            }
                        }
                        else
                        {
                            if (dirIndex == 1 || dirIndex == 3)
                            {
                                bPassedSignal = false;
                            }
                        }
                    }
                    else
                    {
                        if (cycledTime <= signal.TimeNS)
                        {
                            if (dirIndex == 1 || dirIndex == 3)
                            {
                                bPassedSignal = false;
                            }
                        }
                        else
                        {
                            if (dirIndex == 0 || dirIndex == 2)
                            {
                                bPassedSignal = false;
                            }
                        }
                    }
                }

                if (bPassedSignal == false)
                {
                    positionQueue.push(position);

                    continue;
                }

                visited[nextRow][nextCol] = true;
                positionQueue.push({ nextRow, nextCol });
            }
        }

        ++time;
    }

    return false;
}

int main()
{
    while (true)
    {
        int mapSizeRow;
        int mapSizeCol;

        std::cin >> mapSizeRow >> mapSizeCol;

        if (mapSizeRow == 0 && mapSizeCol == 0)
        {
            break;
        }

        char map[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
        unsigned int signalsCount = 0;

        Position startPosition;
        Position endPosition;

        for (unsigned int row = 0; row < mapSizeRow; ++row)
        {
            std::string mapRowString;
            std::cin >> mapRowString;

            for (unsigned int col = 0; col < mapSizeCol; ++col)
            {
                char mapState = mapRowString[col];
                map[row][col] = mapState;

                if (mapState == 'A')
                {
                    startPosition.Row = row;
                    startPosition.Col = col;
                }
                else if (mapState == 'B')
                {
                    endPosition.Row = row;
                    endPosition.Col = col;
                }
                else if (mapState >= '0' && mapState <= '9')
                {
                    signalsCount++;
                }
            }
        }

        std::vector<Signal> signals;
        for (unsigned int i = 0; i < signalsCount; ++i)
        {
            unsigned int signalIndex;
            char start;
            unsigned int timeEW;
            unsigned int timeNS;

            std::cin >> signalIndex >> start >> timeEW >> timeNS;

            Signal signal;
            signal.bStartEW = (start == '-' ? true : false);
            signal.TimeEW = timeEW;
            signal.TimeNS = timeNS;

            signals.push_back(signal);
        }

        unsigned int time = 0;
        bool bArrived = GetMinimumArrivalTime(&time, signals, map, mapSizeRow, mapSizeCol, startPosition, endPosition);

        if (bArrived)
        {
            std::cout << time << std::endl;
        }
        else
        {
            std::cout << "impossible" << std::endl;
        }
    }

    return 0;
}