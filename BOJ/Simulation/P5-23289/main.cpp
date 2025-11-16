
#include <iostream>
#include <vector>
#include <queue>
#include <cassert>

#define MAX_HOUSE_SIZE (20)
#define MAX_WALLS_SIZE (4U)
#define MAX_WIND_MOVE_SIZE (3U)
#define WIND_FIRST_POSITION_INDEX (1U)
#define HEATER_ADD_TEMPERATURE (5U)
#define MIN_HEATER_ADD_TEMPERATURE (0U)
#define MAX_MOVE_WIND_WALL_CHECK_SIZE (2U)
#define MAX_ATE_CHOCOLATE_COUNT (100U)

enum class eDirection : unsigned int
{
    Right = 0,
    Left,
    Up,
    Down
};

struct Position
{
    int Row;
    int Col;
};

struct Space
{
    unsigned int Temperature;
    bool Walls[MAX_WALLS_SIZE];
};

struct Heater
{
    eDirection WindDirection;
    Position Pos;
};

struct WindInfo
{
    Position MovePosition;
    Position WallCheckPosition;
    eDirection WallCheckDirection[MAX_MOVE_WIND_WALL_CHECK_SIZE];
};

static const WindInfo WIND_MOVE_INFOS[MAX_WALLS_SIZE][MAX_WIND_MOVE_SIZE] =
{
    // R
    {
        { { -1, 1 }, { -1, 0 }, { eDirection::Down, eDirection::Right } },
        { { 0, 1 }, { 0, 0 }, { eDirection::Right, eDirection::Right } },
        { { 1, 1 }, { 1, 0 }, { eDirection::Up, eDirection::Right } } 
    },
    
    // L
    {
        { { -1, -1 }, { -1, 0 }, { eDirection::Down, eDirection::Left } },
        { { 0, -1 }, { 0, 0 }, { eDirection::Left, eDirection::Left } },
        { { 1, -1 }, { 1, 0 }, { eDirection::Up, eDirection::Left } }
    },
    
    // U
    {
        { { -1, -1 }, { 0, -1 }, { eDirection::Right, eDirection::Up } },
        { { -1, 0 }, { 0, 0 }, { eDirection::Up, eDirection::Up } },
        { { -1, 1 }, { 0, 1 }, { eDirection::Left, eDirection::Up } }
    },

    // D
    {
        { { 1, -1 }, { 0, -1 }, { eDirection::Right, eDirection::Down } },
        { { 1, 0 }, { 0, 0 }, { eDirection::Down, eDirection::Down } },
        { { 1, 1 }, { 0, 1 }, { eDirection::Left, eDirection::Down } }
    }
};

static int sHouseSizeRow = 0;
static int sHouseSizeCol = 0;
static unsigned int sTargetTemperature = 0;

bool IsPositionOnBoundary(const Position& position)
{
    if (position.Row < 0 || position.Row >= sHouseSizeRow ||
        position.Col < 0 || position.Col >= sHouseSizeCol)
    {
        return false;
    }

    return true;
}

static void AdjustTemperature(Space outAdjustedHouse[][MAX_HOUSE_SIZE], const Position& higher, const Position& lower, const Space house[][MAX_HOUSE_SIZE])
{
    int addTemperature = 0;

    addTemperature = (house[higher.Row][higher.Col].Temperature - house[lower.Row][lower.Col].Temperature) / 4;
    outAdjustedHouse[higher.Row][higher.Col].Temperature -= addTemperature;
    outAdjustedHouse[lower.Row][lower.Col].Temperature += addTemperature;
}

static void TestAdjustTemperature()
{
    Space house[MAX_HOUSE_SIZE][MAX_HOUSE_SIZE] = { 0, };

    std::cin >> sHouseSizeRow >> sHouseSizeCol;
    for (int row = 0; row < sHouseSizeRow; ++row)
    {
        for (int col = 0; col < sHouseSizeCol; ++col)
        {
            unsigned int state = 0;
            std::cin >> state;

            house[row][col].Temperature = state;
        }
    }

    unsigned int wallsCount = 0;
    std::cin >> wallsCount;

    for (unsigned int i = 0; i < wallsCount; ++i)
    {
        Position wallPos = { 0, };
        unsigned int wallState = 0;

        std::cin >> wallPos.Row >> wallPos.Col >> wallState;
        wallPos.Row--;
        wallPos.Col--;

        assert(wallPos.Row >= 0);
        assert(wallPos.Col >= 0);

        if (wallState == 0)
        {
            assert(wallPos.Row >= 1);

            house[wallPos.Row][wallPos.Col].Walls[static_cast<unsigned int>(eDirection::Up)] = true;
            house[wallPos.Row - 1][wallPos.Col].Walls[static_cast<unsigned int>(eDirection::Down)] = true;
        }
        else
        {
            assert(wallPos.Col < sHouseSizeCol - 1);

            house[wallPos.Row][wallPos.Col].Walls[static_cast<unsigned int>(eDirection::Right)] = true;
            house[wallPos.Row][wallPos.Col + 1].Walls[static_cast<unsigned int>(eDirection::Left)] = true;
        }
    }

    // Adjust temperature
    Space constantHouse[MAX_HOUSE_SIZE][MAX_HOUSE_SIZE];
    for (int row = 0; row < sHouseSizeRow; ++row)
    {
        for (int col = 0; col < sHouseSizeCol; ++col)
        {
            constantHouse[row][col] = house[row][col];
        }
    }

    bool adjustedVisited[MAX_HOUSE_SIZE][MAX_HOUSE_SIZE] = { false, };

    for (int row = 0; row < sHouseSizeRow; ++row)
    {
        for (int col = 0; col < sHouseSizeCol; ++col)
        {

            for (unsigned int adjacentIndex = 0; adjacentIndex < MAX_WALLS_SIZE; ++adjacentIndex)
            {
                Position adjacentPosition =
                {
                    row + WIND_MOVE_INFOS[adjacentIndex][WIND_FIRST_POSITION_INDEX].MovePosition.Row,
                    col + WIND_MOVE_INFOS[adjacentIndex][WIND_FIRST_POSITION_INDEX].MovePosition.Col
                };

                if (IsPositionOnBoundary(adjacentPosition) == false)
                {
                    continue;
                }

                if (constantHouse[row][col].Walls[adjacentIndex] || adjustedVisited[adjacentPosition.Row][adjacentPosition.Col])
                {
                    continue;
                }

                Position position = { row, col };
                if (constantHouse[row][col].Temperature <= constantHouse[adjacentPosition.Row][adjacentPosition.Col].Temperature)
                {
                    AdjustTemperature(house, adjacentPosition, position, constantHouse);
                }
                else
                {
                    AdjustTemperature(house, position, adjacentPosition, constantHouse);
                }
            }

            adjustedVisited[row][col] = true;
        }
    }

    return;
}

int main()
{
    //TestAdjustTemperature();

    Space house[MAX_HOUSE_SIZE][MAX_HOUSE_SIZE] = { 0, };

    std::cin >> sHouseSizeRow >> sHouseSizeCol >> sTargetTemperature;
    
    std::vector<Position> targetPositions;
    std::vector<Heater> heaters;

    for (int row = 0; row < sHouseSizeRow; ++row)
    {
        for (int col = 0; col < sHouseSizeCol; ++col)
        {
            unsigned int state = 0;
            std::cin >> state;

            if (state == 0)
            {
                continue;
            }
            else if (state == 5)
            {
                targetPositions.push_back({ row, col });
            }
            else
            {
                heaters.push_back({ static_cast<eDirection>(state - 1), { row, col } });
            }
        }
    }

    unsigned int wallsCount = 0;
    std::cin >> wallsCount;
    
    for (unsigned int i = 0; i < wallsCount; ++i)
    {
        Position wallPos = { 0, };
        unsigned int wallState = 0;

        std::cin >> wallPos.Row >> wallPos.Col >> wallState;
        wallPos.Row--;
        wallPos.Col--;

        assert(wallPos.Row >= 0);
        assert(wallPos.Col >= 0);

        if (wallState == 0)
        {
            assert(wallPos.Row >= 1);

            house[wallPos.Row][wallPos.Col].Walls[static_cast<unsigned int>(eDirection::Up)] = true;
            house[wallPos.Row - 1][wallPos.Col].Walls[static_cast<unsigned int>(eDirection::Down)] = true;
        }
        else
        {
            assert(wallPos.Col < sHouseSizeCol - 1);

            house[wallPos.Row][wallPos.Col].Walls[static_cast<unsigned int>(eDirection::Right)] = true;
            house[wallPos.Row][wallPos.Col + 1].Walls[static_cast<unsigned int>(eDirection::Left)] = true;
        }
    }

    unsigned int ateChocolate = 0;

    // Todo: Has limit
    while (ateChocolate <= MAX_ATE_CHOCOLATE_COUNT)
    {
        // Turn on heaters
        for (Heater heater : heaters)
        {
            bool visited[MAX_HOUSE_SIZE][MAX_HOUSE_SIZE] = { false, };
            std::queue<Position> windPositions;

            unsigned int windDirectionIndex = static_cast<unsigned int>(heater.WindDirection);
            Position nextWindPosition = 
            {
                heater.Pos.Row + WIND_MOVE_INFOS[windDirectionIndex][WIND_FIRST_POSITION_INDEX].MovePosition.Row,
                heater.Pos.Col + WIND_MOVE_INFOS[windDirectionIndex][WIND_FIRST_POSITION_INDEX].MovePosition.Col
            };

            windPositions.push(nextWindPosition);
            visited[nextWindPosition.Row][nextWindPosition.Col] = true;

            unsigned int heaterAddTemperature = HEATER_ADD_TEMPERATURE;
            house[nextWindPosition.Row][nextWindPosition.Col].Temperature += heaterAddTemperature;

            while (windPositions.empty() == false)
            {
                heaterAddTemperature--;

                unsigned int windPositionsSize = windPositions.size();
                for (unsigned int i = 0; i < windPositionsSize; ++i)
                {
                    Position windPosition = windPositions.front();
                    windPositions.pop();

                    for (unsigned int windMoveIndex = 0; windMoveIndex < MAX_WIND_MOVE_SIZE; ++windMoveIndex)
                    {
                        WindInfo windInfo = WIND_MOVE_INFOS[windDirectionIndex][windMoveIndex];

                        nextWindPosition =
                        {
                            windPosition.Row + windInfo.MovePosition.Row,
                            windPosition.Col + windInfo.MovePosition.Col
                        };

                        if (IsPositionOnBoundary(nextWindPosition) == false)
                        {
                            continue;
                        }

                        if (visited[nextWindPosition.Row][nextWindPosition.Col])
                        {
                            continue;
                        }

                        if (heaterAddTemperature == MIN_HEATER_ADD_TEMPERATURE)
                        {
                            continue;
                        }

                        // Todo: If wall, continue
                        Position wallCheckPosition =
                        {
                            windPosition.Row + windInfo.WallCheckPosition.Row,
                            windPosition.Col + windInfo.WallCheckPosition.Col
                        };

                        bool bWall = false;
                        for (unsigned int wallCheckIndex = 0; wallCheckIndex < MAX_MOVE_WIND_WALL_CHECK_SIZE; ++wallCheckIndex)
                        {
                            unsigned int checkDirectionIndex = static_cast<unsigned int>(windInfo.WallCheckDirection[wallCheckIndex]);
                            if (house[wallCheckPosition.Row][wallCheckPosition.Col].Walls[checkDirectionIndex])
                            {
                                bWall = true;
                                break;
                            }
                        }

                        if (bWall)
                        {
                            continue;
                        }

                        windPositions.push(nextWindPosition);
                        visited[nextWindPosition.Row][nextWindPosition.Col] = true;
                        house[nextWindPosition.Row][nextWindPosition.Col].Temperature += heaterAddTemperature;
                    }
                }    
            }
        }

        // Adjust temperature
        Space constantHouse[MAX_HOUSE_SIZE][MAX_HOUSE_SIZE];
        for (int row = 0; row < sHouseSizeRow; ++row)
        {
            for (int col = 0; col < sHouseSizeCol; ++col)
            {
                constantHouse[row][col] = house[row][col];
            }
        }

        bool adjustedVisited[MAX_HOUSE_SIZE][MAX_HOUSE_SIZE] = { false, };

        for (int row = 0; row < sHouseSizeRow; ++row)
        {
            for (int col = 0; col < sHouseSizeCol; ++col)
            {
                
                for (unsigned int adjacentIndex = 0; adjacentIndex < MAX_WALLS_SIZE; ++adjacentIndex)
                {
                    Position adjacentPosition =
                    {
                        row + WIND_MOVE_INFOS[adjacentIndex][WIND_FIRST_POSITION_INDEX].MovePosition.Row,
                        col + WIND_MOVE_INFOS[adjacentIndex][WIND_FIRST_POSITION_INDEX].MovePosition.Col
                    };

                    if (IsPositionOnBoundary(adjacentPosition) == false)
                    {
                        continue;
                    }

                    if (constantHouse[row][col].Walls[adjacentIndex] || adjustedVisited[adjacentPosition.Row][adjacentPosition.Col])
                    {
                        continue;
                    }
                    
                    Position position = { row, col };
                    if (constantHouse[row][col].Temperature <= constantHouse[adjacentPosition.Row][adjacentPosition.Col].Temperature)
                    {
                        AdjustTemperature(house, adjacentPosition, position, constantHouse);
                    }
                    else
                    {
                        AdjustTemperature(house, position, adjacentPosition, constantHouse);
                    }
                }

                adjustedVisited[row][col] = true;
            }
        }

        // Remove outskirts temperature
        for (int row = 0; row < sHouseSizeRow; ++row)
        {
            unsigned int leftMostTemperature = house[row][0].Temperature;
            unsigned int rightMostTemparature = house[row][sHouseSizeCol - 1].Temperature;

            house[row][0].Temperature = (leftMostTemperature > 0) ? leftMostTemperature - 1 : leftMostTemperature;
            house[row][sHouseSizeCol - 1].Temperature = (rightMostTemparature > 0) ? rightMostTemparature - 1 : rightMostTemparature;
        }

        for (int col = 1; col < sHouseSizeCol - 1; ++col)
        {
            unsigned int topMostTemperature = house[0][col].Temperature;
            unsigned int buttomMostTemparature = house[sHouseSizeRow - 1][col].Temperature;

            house[0][col].Temperature = (topMostTemperature > 0) ? topMostTemperature - 1 : topMostTemperature;
            house[sHouseSizeRow - 1][col].Temperature = (buttomMostTemparature > 0) ? buttomMostTemparature - 1 : buttomMostTemparature;
        }

        // Eat chocolate
        ateChocolate++;

        // Check target spaces
        bool bInspectionComplete = true;
        for (const Position& position : targetPositions)
        {
            if (house[position.Row][position.Col].Temperature < sTargetTemperature)
            {
                bInspectionComplete = false;
                break;
            }
        }

        if (bInspectionComplete)
        {
            break;
        }
    }

    std::cout << ((ateChocolate <= MAX_ATE_CHOCOLATE_COUNT) ? ateChocolate : MAX_ATE_CHOCOLATE_COUNT + 1);

    return 0;
}

