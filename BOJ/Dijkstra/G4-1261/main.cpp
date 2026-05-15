
#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>

#define MAX_MAP_SIZE (101U)
#define MAX_DIRECTIONS (4U)

struct Position
{
    int Row;
    int Col;
};

struct Destination
{
public:
    bool operator<(const Destination& other) const
    {
        return WallBreakCount > other.WallBreakCount;
    }

    Position Pos;
    unsigned int WallBreakCount;
};

static const Position NEXT_POSITIONS[MAX_DIRECTIONS] =
{
    { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 }
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int mapRowSize;
    int mapColSize;

    std::cin >> mapColSize >> mapRowSize;
    
    unsigned int map[MAX_MAP_SIZE][MAX_MAP_SIZE];
    for (int row = 0; row < mapRowSize; ++row)
    {
        std::string mapRowString;
        std::cin >> mapRowString;

        for (int col = 0; col < mapColSize; ++col)
        {
            map[row][col] = static_cast<unsigned int>(mapRowString[col] - '0');
        }
    }

    unsigned int minWallBreakCounts[MAX_MAP_SIZE][MAX_MAP_SIZE];
    std::fill(&minWallBreakCounts[0][0], &minWallBreakCounts[0][0] + (MAX_MAP_SIZE * MAX_MAP_SIZE), UINT_MAX);

    std::priority_queue<Destination> destinationQueueAscend;
    destinationQueueAscend.push({ { 0, 0 }, 0 });
    minWallBreakCounts[0][0] = 0;

    while (destinationQueueAscend.empty() == false)
    {
        Destination destination = destinationQueueAscend.top();
        destinationQueueAscend.pop();

        if (destination.WallBreakCount > minWallBreakCounts[destination.Pos.Row][destination.Pos.Col])
        {
            continue;
        }

        for (unsigned int dirIndex = 0; dirIndex < MAX_DIRECTIONS; ++dirIndex)
        {
            int nextRow = destination.Pos.Row + NEXT_POSITIONS[dirIndex].Row;
            int nextCol = destination.Pos.Col + NEXT_POSITIONS[dirIndex].Col;

            if (nextRow < 0 || nextRow >= mapRowSize || nextCol < 0 || nextCol >= mapColSize)
            {
                continue;
            }

            unsigned int nextWallBreakCount = destination.WallBreakCount + map[nextRow][nextCol];
            if (nextWallBreakCount >= minWallBreakCounts[nextRow][nextCol])
            {
                continue;
            }

            minWallBreakCounts[nextRow][nextCol] = nextWallBreakCount;
            destinationQueueAscend.push({ { nextRow, nextCol }, nextWallBreakCount });
        }
    }

    std::cout << minWallBreakCounts[mapRowSize - 1][mapColSize - 1];

    return  0;
}