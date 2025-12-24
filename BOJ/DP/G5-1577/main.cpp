#include <iostream>
#include <unordered_set>
#include <string>
#include <queue>

#define MAX_STRING_ROAD_SIZE (8U)
#define MAX_MAP_SIZE (101)
#define MAX_MOVE_POSITIONS_SIZE (2)

struct Position
{
    int Row;
    int Col;
};

static long long sCases[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

static std::unordered_set<std::string> sRepairRoads;

static unsigned int sMapSizeRow;
static unsigned int sMapSizeCol;

// N, E
static Position MOVE_POSITIONS[MAX_MOVE_POSITIONS_SIZE] = { { -1, 0 }, { 0, 1 } };

static void TransformRoadToString(const Position& start, const Position& end, std::string* outRoadString)
{
    outRoadString->append(std::to_string(start.Row));
    outRoadString->append(",");
    outRoadString->append(std::to_string(start.Col));

    outRoadString->append("-");

    outRoadString->append(std::to_string(end.Row));
    outRoadString->append(",");
    outRoadString->append(std::to_string(end.Col));
}

int main()
{
    std::cin >> sMapSizeCol >> sMapSizeRow;
    sMapSizeRow++;
    sMapSizeCol++;

    unsigned int repairingRoadsCount;
    std::cin >> repairingRoadsCount;

    for (unsigned int i = 0; i < repairingRoadsCount; ++i)
    {
        // Transform coordinates: x, y -> M - y, x
        Position startPosition;

        std::cin >> startPosition.Col >> startPosition.Row;
        startPosition.Row = sMapSizeRow - 1 - startPosition.Row;

        Position endPosition;

        std::cin >> endPosition.Col >> endPosition.Row;
        endPosition.Row = sMapSizeRow - 1 - endPosition.Row;

        std::string repairRoadString;
        repairRoadString.reserve(MAX_STRING_ROAD_SIZE);
        TransformRoadToString(startPosition, endPosition, &repairRoadString);
        sRepairRoads.insert(repairRoadString);

        std::string reveredRoadString;
        reveredRoadString.reserve(MAX_STRING_ROAD_SIZE);
        TransformRoadToString(endPosition, startPosition, &reveredRoadString);
        sRepairRoads.insert(reveredRoadString);
    }

    bool visited[MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };

    std::queue<Position> positionQueue;
    Position startPosition = { sMapSizeRow - 1, 0 };
    sCases[startPosition.Row][startPosition.Col] = 1;

    positionQueue.push(startPosition);
    
    while (positionQueue.empty() == false)
    {
        Position position = positionQueue.front();
        positionQueue.pop();

        for (unsigned int i = 0; i < MAX_MOVE_POSITIONS_SIZE; ++i)
        {
            Position nextPosition;
            nextPosition.Row = position.Row + MOVE_POSITIONS[i].Row;
            nextPosition.Col = position.Col + MOVE_POSITIONS[i].Col;

            if (nextPosition.Row >= sMapSizeRow || nextPosition.Col >= sMapSizeCol)
            {
                continue;
            }

            std::string roadString;
            roadString.reserve(MAX_STRING_ROAD_SIZE);
            TransformRoadToString(position, nextPosition, &roadString);

            if (sRepairRoads.find(roadString) != sRepairRoads.end())
            {
                continue;
            }

            sCases[nextPosition.Row][nextPosition.Col] += sCases[position.Row][position.Col];

            if (visited[nextPosition.Row][nextPosition.Col])
            {
                continue;
            }

            visited[nextPosition.Row][nextPosition.Col] = true;
            positionQueue.push(nextPosition);
        }
    }

    std::cout << sCases[0][sMapSizeCol - 1];

    return 0;
}