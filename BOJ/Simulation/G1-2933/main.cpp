
#include <iostream>
#include <cstring>
#include <string>
#include <queue>

#define MAX_CAVE_ROW_SIZE (100U)
#define MAX_CAVE_COL_SIZE (100U)

#define MAX_MOVE_DIRECTIONS (4U)

enum class eTurn : unsigned int
{
    Left = 0,
    Right
};

struct Position
{
    int Row;
    int Col;
};

enum class Direction : unsigned int
{
    North = 0,
    East,
    South,
    West
};

static const Position MOVE_DIRECTIONS[MAX_MOVE_DIRECTIONS] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };

int main()
{
    int cave[MAX_CAVE_ROW_SIZE][MAX_CAVE_COL_SIZE] = { 0, };
    bool bVisited[MAX_CAVE_ROW_SIZE][MAX_CAVE_COL_SIZE] = { false, };

    int caveRowSize = 0;
    int caveColSize = 0;

    std::cin >> caveRowSize >> caveColSize;

    std::string caveRowState;
    for (int row = 0; row < caveRowSize; ++row)
    {
        std::cin >> caveRowState;
        for (int col = 0; col < caveColSize; ++col)
        {
            if (caveRowState[col] == 'x')
            {
                cave[row][col] = 1;
            }
        }
    }

    int clusterId = 1;

    unsigned int maxSpearThrowCount = 0;
    std::cin >> maxSpearThrowCount;

    for (unsigned int throwCount = 0; throwCount < maxSpearThrowCount; ++throwCount)
    {
        int throwHeight = 0;
        std::cin >> throwHeight;

        int throwRow = caveRowSize - throwHeight;

        eTurn currentTurn = (throwCount % 2) == 0 ? eTurn::Left : eTurn::Right;
        if (currentTurn == eTurn::Left)
        {
            for (int col = 0; col < caveColSize; ++col)
            {
                if (cave[throwRow][col] > 0)
                {
                    cave[throwRow][col] = 0;

                    break;
                }
            }
        }
        else
        {
            for (int col = caveColSize - 1; col >= 0; --col)
            {
                if (cave[throwRow][col] > 0)
                {
                    cave[throwRow][col] = 0;

                    break;
                }
            }
        }

        // Specify clusters
        memset(bVisited, false, sizeof(bVisited));

        int floatingClusterId = -1;
        Position floatingClusterStartPosition = { 0, 0 };

        for (int row = 0; row < caveRowSize; ++row)
        {
            for (int col = 0; col < caveColSize; ++col)
            {
                if (cave[row][col] == 0 || bVisited[row][col])
                {
                    continue;
                }

                bool bFloatingCluster = true;

                std::queue<Position> mineralPositionQueue;
                mineralPositionQueue.push({ row, col });
                
                cave[row][col] = clusterId;
                bVisited[row][col] = true;
                
                while (mineralPositionQueue.empty() == false)
                {
                    Position position = mineralPositionQueue.front();
                    mineralPositionQueue.pop();

                    if (bFloatingCluster)
                    {
                        int buttomCheckRow = position.Row + MOVE_DIRECTIONS[static_cast<unsigned int>(Direction::South)].Row;
                        if (buttomCheckRow >= caveRowSize)
                        {
                            bFloatingCluster = false;
                        }
                    }

                    for (unsigned int moveIndex = 0; moveIndex < MAX_MOVE_DIRECTIONS; ++moveIndex)
                    {
                        int nextRow = position.Row + MOVE_DIRECTIONS[moveIndex].Row;
                        int nextCol = position.Col + MOVE_DIRECTIONS[moveIndex].Col;

                        if (nextRow < 0 || nextRow >= caveRowSize || nextCol < 0 || nextCol >= caveColSize)
                        {
                            continue;
                        }

                        if (cave[nextRow][nextCol] == 0 || bVisited[nextRow][nextCol])
                        {
                            continue;
                        }

                        bVisited[nextRow][nextCol] = true;
                        cave[nextRow][nextCol] = clusterId;

                        mineralPositionQueue.push({ nextRow, nextCol });
                    }
                }

                if (bFloatingCluster)
                {
                    floatingClusterId = clusterId;
                    floatingClusterStartPosition = { row, col };
                }

                clusterId++;
            }
        }

        if (floatingClusterId == -1)
        {
            continue;
        }

        // Get floating cluster buttom blocks
        memset(bVisited, false, sizeof(bVisited));

        std::queue<Position> floatingClusterDrawingQueue;
        std::queue<Position> floatingClusterButtomBlockQueue;

        std::queue<Position> floatingClusterQueue;
        floatingClusterQueue.push(floatingClusterStartPosition);
        bVisited[floatingClusterStartPosition.Row][floatingClusterStartPosition.Col] = true;

        while (floatingClusterQueue.empty() == false)
        {
            Position position = floatingClusterQueue.front();
            floatingClusterQueue.pop();

            cave[position.Row][position.Col] = 0;
            floatingClusterDrawingQueue.push(position);

            int buttomCheckRow = position.Row + MOVE_DIRECTIONS[static_cast<unsigned int>(Direction::South)].Row;
            if (cave[buttomCheckRow][position.Col] == 0)
            {
                floatingClusterButtomBlockQueue.push(position);
            }

            for (unsigned int moveIndex = 0; moveIndex < MAX_MOVE_DIRECTIONS; ++moveIndex)
            {
                int nextRow = position.Row + MOVE_DIRECTIONS[moveIndex].Row;
                int nextCol = position.Col + MOVE_DIRECTIONS[moveIndex].Col;

                if (nextRow < 0 || nextRow >= caveRowSize || nextCol < 0 || nextCol >= caveColSize)
                {
                    continue;
                }

                if (cave[nextRow][nextCol] != floatingClusterId || bVisited[nextRow][nextCol])
                {
                    continue;
                }

                floatingClusterQueue.push({ nextRow, nextCol });
                bVisited[nextRow][nextCol] = true;
            }
        }
        
        // Get shortest distance block
        unsigned int shortestDistance = MAX_CAVE_ROW_SIZE;
        while (floatingClusterButtomBlockQueue.empty() == false)
        {
            Position position = floatingClusterButtomBlockQueue.front();
            floatingClusterButtomBlockQueue.pop();

            unsigned int distance = 0;
            int row = position.Row;
            while (true)
            {
                ++row;

                if (row >= caveRowSize || cave[row][position.Col] != 0)
                {
                    break;
                }

                ++distance;
            }

            if (cave[row][position.Col] == floatingClusterId)
            {
                continue;
            }

            if (distance < shortestDistance)
            {
                shortestDistance = distance;
            }
        }

        // Move floating cluster
        while (floatingClusterDrawingQueue.empty() == false)
        {
            Position position = floatingClusterDrawingQueue.front();
            floatingClusterDrawingQueue.pop();

            cave[position.Row + shortestDistance][position.Col] = floatingClusterId;
        }
    }

    // Print minerals
    for (int row = 0; row < caveRowSize; ++row)
    {
        for (int col = 0; col < caveColSize; ++col)
        {
            if (cave[row][col] == 0)
            {
                std::cout << '.';

                continue;
            }

            std::cout << 'x';
        }

        std::cout << std::endl;
    }

    return 0;
}