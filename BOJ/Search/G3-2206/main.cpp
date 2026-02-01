
#include <iostream>
#include <queue>

#define MAX_DIRECTIONS_SIZE (4U)

#define MAX_BREAK_COUNT (1U)
#define MAX_MAP_SIZE (1001U)

struct Position
{
    int Row;
    int Col;
};

struct MapInfo
{
    Position Pos;
    unsigned int BreakCount;
};

static const Position MOVE_POSITIONS[MAX_DIRECTIONS_SIZE] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int main()
{
    int mapRowSize;
    int mapColSize;

    std::cin >> mapRowSize >> mapColSize;

    bool bWalls[MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };
    for (int row = 0; row < mapRowSize; ++row)
    {
        std::string mapRowString;
        std::cin >> mapRowString;

        for (int col = 0; col < mapColSize; ++col)
        {
            bWalls[row][col] = (mapRowString[col] == '1' ? true : false);
        }
    }

    bool bVisited[MAX_BREAK_COUNT + 1][MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };
    
    MapInfo startInfo = { { 0, 0 }, 0 };

    std::queue<MapInfo> mapInfoQueue;
    mapInfoQueue.push(startInfo);
    
    bVisited[0][startInfo.Pos.Row][startInfo.Pos.Col] = true;

    bool bExit = false;
    unsigned int moveCount = 0;
    while (mapInfoQueue.empty() == false)
    {
        unsigned int queueSize = mapInfoQueue.size();
        for (unsigned int i = 0; i < queueSize; ++i)
        {
            MapInfo mapInfo = mapInfoQueue.front();
            mapInfoQueue.pop();

            if (mapInfo.Pos.Row == mapRowSize - 1 && mapInfo.Pos.Col == mapColSize - 1)
            {
                bExit = true;

                goto COMPLETE_LABEL;
            }

            for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS_SIZE; ++dirIndex)
            {
                int nextRow = mapInfo.Pos.Row + MOVE_POSITIONS[dirIndex].Row;
                int nextCol = mapInfo.Pos.Col + MOVE_POSITIONS[dirIndex].Col;

                if (nextRow < 0 || nextRow >= mapRowSize ||
                    nextCol < 0 || nextCol >= mapColSize)
                {
                    continue;
                }

                if (bVisited[mapInfo.BreakCount][nextRow][nextCol])
                {
                    continue;
                }

                if (bWalls[nextRow][nextCol])
                {
                    if (mapInfo.BreakCount < MAX_BREAK_COUNT)
                    {
                        bVisited[mapInfo.BreakCount + 1][nextRow][nextCol] = true;
                        mapInfoQueue.push({ { nextRow, nextCol }, mapInfo.BreakCount + 1 });
                    }

                    continue;
                }

                bVisited[mapInfo.BreakCount][nextRow][nextCol] = true;
                mapInfoQueue.push({ { nextRow, nextCol }, mapInfo.BreakCount });
            }
        }

        ++moveCount;
    }

COMPLETE_LABEL:

    if (bExit)
    {
        std::cout << (moveCount + 1);
    }
    else
    {
        std::cout << -1;
    }

    return 0;
}