
#include <iostream>
#include <queue>
#include <string>
#include <cassert>

#define MAX_NUMBER (1000000U)
#define MAX_MAP_SIZE (2500U)
#define MAX_MOVE_DIRECTIONS_SIZE (6U)
#define MAX_NUMBERING_MOVES_SIZE (5U)

static unsigned int sStartNumber;
static unsigned int sExitNumber;

enum class Direction : unsigned int
{
    North = 0,
    NorthEast,
    SouthEast,
    South,
    SouthWest,
    NorthWest
};

struct Position
{
    int Row;
    int Col;
};

struct MapInfo
{
    Position Pos;
    unsigned int Number;
};

struct PersonInfo
{
    std::string Paths;
    MapInfo MapInformation;
};

// N, NE, SE, S, SW, NW
const static Position MOVE_DIRECTIONS[MAX_MOVE_DIRECTIONS_SIZE] = { { -2, 0 }, { -1, 1 }, { 1, 1 }, { 2, 0 }, { 1, -1 }, { -1, -1 } };

// Always starts on 12
const static Direction NUMBERING_MOVE_INDEXES[MAX_NUMBERING_MOVES_SIZE] =
{ 
    Direction::SouthEast, 
    Direction::South, 
    Direction::SouthWest, 
    Direction::NorthWest, 
    Direction::North
};

static unsigned int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };

// Returns updated number, position
static void UpdateNumberOnMap(MapInfo* outMapInfo, const Direction moveDirection)
{
    outMapInfo->Pos.Row += MOVE_DIRECTIONS[static_cast<unsigned int>(moveDirection)].Row;
    outMapInfo->Pos.Col += MOVE_DIRECTIONS[static_cast<unsigned int>(moveDirection)].Col;

    sMap[outMapInfo->Pos.Row][outMapInfo->Pos.Col] = outMapInfo->Number;
    outMapInfo->Number++;
}

static void GetMinPaths(PersonInfo* outMinMovePaths, const MapInfo& startInfo, const unsigned int targetNumber)
{
    bool visited[MAX_MAP_SIZE][MAX_MAP_SIZE] = { false, };

    std::string startPath;
    startPath.append(std::to_string(startInfo.Number));
    startPath.append(" ");

    PersonInfo personInfo = { startPath, startInfo };

    std::queue<PersonInfo> pathsQueue;
    pathsQueue.push(personInfo);

    while (pathsQueue.empty() == false)
    {
        personInfo = pathsQueue.front();
        pathsQueue.pop();

        if (personInfo.MapInformation.Number == targetNumber)
        {
            *outMinMovePaths = personInfo;
            
            return;
        }

        for (unsigned int dirIndex = 0; dirIndex < MAX_MOVE_DIRECTIONS_SIZE; ++dirIndex)
        {
            int nextRow = personInfo.MapInformation.Pos.Row + MOVE_DIRECTIONS[dirIndex].Row;
            int nextCol = personInfo.MapInformation.Pos.Col + MOVE_DIRECTIONS[dirIndex].Col;

            assert(nextRow >= 0 && nextRow < MAX_MAP_SIZE);
            assert(nextCol >= 0 && nextCol < MAX_MAP_SIZE);

            if (sMap[nextRow][nextCol] == 0 || sMap[nextRow][nextCol] > MAX_NUMBER)
            {
                continue;
            }

            if (visited[nextRow][nextCol])
            {
                continue;
            }

            PersonInfo newPersonInfo;
            newPersonInfo.MapInformation.Number = sMap[nextRow][nextCol];
            
            newPersonInfo.MapInformation.Pos.Row = nextRow;
            newPersonInfo.MapInformation.Pos.Col = nextCol;

            newPersonInfo.Paths.append(personInfo.Paths);
            newPersonInfo.Paths.append(std::to_string(sMap[nextRow][nextCol]));
            newPersonInfo.Paths.append(" ");

            pathsQueue.push(newPersonInfo);
            visited[nextRow][nextCol] = true;
        }
    }

    assert(false);
}

int main()
{
    std::cin >> sStartNumber >> sExitNumber;

    // Number map
    Position numberStartPosition = { MAX_MAP_SIZE / 2 - 1, MAX_MAP_SIZE / 2 - 1 };
    sMap[numberStartPosition.Row][numberStartPosition.Col] = 1;

    MapInfo mapInfo = { numberStartPosition, 2 };
    UpdateNumberOnMap(&mapInfo, Direction::North);

    unsigned int maxMoveCount = 1;
    while (true)
    {
        for (unsigned int numberingIndex = 0; numberingIndex < MAX_NUMBERING_MOVES_SIZE; ++numberingIndex)
        {
            Direction moveDirection = NUMBERING_MOVE_INDEXES[numberingIndex];

            for (unsigned int moveCount = 0; moveCount < maxMoveCount; ++moveCount)
            {
                UpdateNumberOnMap(&mapInfo, moveDirection);
            }
        }

        // Place on 12
        UpdateNumberOnMap(&mapInfo, Direction::North);

        for (unsigned int moveCount = 0; moveCount < maxMoveCount; ++moveCount)
        {
            UpdateNumberOnMap(&mapInfo, Direction::NorthEast);
        }

        if (mapInfo.Number > MAX_NUMBER)
        {
            break;
        }

        maxMoveCount++;
    }

    // Find start, end room position
    PersonInfo exitInfo;
    MapInfo startMapInfo = { numberStartPosition, 1 };
    GetMinPaths(&exitInfo, startMapInfo, sStartNumber);

    startMapInfo = exitInfo.MapInformation;
    GetMinPaths(&exitInfo, startMapInfo, sExitNumber);

    std::cout << exitInfo.Paths;

    return 0;
}