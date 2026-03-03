
#include <climits>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

#define MAX_MAP_SIZE (8U)
#define MAX_WALL_COUNT (3U)
#define MAX_MOVE_POSITIONS (4U)

struct Position
{
    int Row;
    int Col;
};

static const Position MOVE_POSITIONS[] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static int sRowSize;
static int sColSize;

static unsigned int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
static std::vector<Position> sContaminatedPositions;

static void GetMinContaminatedCountRecursive(unsigned int wallCount, int index, unsigned int* outMinContaminatedCount)
{
    if (wallCount == MAX_WALL_COUNT)
    {
        unsigned int contaminatedCount = 0;
        
        // Contaminate
        bool bVisited[MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };
        std::queue<Position> contaminatedPositions;
        
        for (const Position& position : sContaminatedPositions)
        {
            contaminatedPositions.push(position);

            bVisited[position.Row][position.Col] = true;
        }

        while (contaminatedPositions.empty() == false)
        {
            Position position = contaminatedPositions.front();
            contaminatedPositions.pop();

            for (unsigned int moveIndex = 0; moveIndex < MAX_MOVE_POSITIONS; ++moveIndex)
            {
                int nextRow = position.Row + MOVE_POSITIONS[moveIndex].Row;
                int nextCol = position.Col + MOVE_POSITIONS[moveIndex].Col;

                if (nextRow < 0 || nextRow >= sRowSize || nextCol < 0 || nextCol >= sColSize)
                {
                    continue;
                }

                if (bVisited[nextRow][nextCol] || sMap[nextRow][nextCol] != 0)
                {
                    continue;
                }

                ++contaminatedCount;
                bVisited[nextRow][nextCol] = true;

                contaminatedPositions.push({ nextRow, nextCol });
            }
        }

        if (contaminatedCount < *outMinContaminatedCount)
        {
            *outMinContaminatedCount = contaminatedCount;
        }

        return;
    }

    int col = index % sColSize;
    for (int row = index / sColSize; row < sRowSize; ++row)
    {
        while (col < sColSize)
        {
            if (sMap[row][col] == 0)
            {
                sMap[row][col] = 1;
                GetMinContaminatedCountRecursive(wallCount + 1, (row * sColSize + col) + 1, outMinContaminatedCount);

                sMap[row][col] = 0;
            }

            ++col;
        }

        col = 0;
    }
}

int main()
{
    std::cin >> sRowSize;
    std::cin >> sColSize;
    
    unsigned int safeCount = 0;
    for (int row = 0; row < sRowSize; ++row)
    {
        for (int col = 0; col < sColSize; ++col)
        {
            unsigned int mapState;
            std::cin >> mapState;

            sMap[row][col] = mapState;
            if (mapState == 0)
            {
                ++safeCount;
            }
            else if (mapState == 2)
            {
                sContaminatedPositions.push_back({ row, col });
            }
        }
    }

    safeCount -= MAX_WALL_COUNT;

    unsigned int minContamintedCount = UINT_MAX;
    GetMinContaminatedCountRecursive(0, 0, &minContamintedCount);

    std::cout << (safeCount - minContamintedCount);

    return 0;
}