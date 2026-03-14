
#include <climits>
#include <cstring>
#include <iostream>
#include <vector>

#define MAX_MAP_SIZE (8U)
#define MAX_CAMERA_TYPES (5U)
#define WALL (6U)
#define EMPTY (0U)

#define DETECTION ('#')

struct Position
{
    int Row;
    int Col;
};

struct Camera
{
    unsigned int Type;
    Position Pos;
};

enum class Direction
{
    North = 0,
    East,
    South,
    West
};

static const Position DETECT_POSITIONS[MAX_CAMERA_TYPES] =
{
    { -1, 0 },
    { 0, 1 },
    { 1, 0 },
    { 0, -1 }
};

static const std::vector<std::vector<Direction>> CAMERA_DETECT_DIRECTIONS[MAX_CAMERA_TYPES] =
{
    {
        {
            Direction::North
        },
        {
            Direction::East
        },
        {
            Direction::South
        },
        {
            Direction::West
        },
    },

    {
        {
            Direction::East, Direction::West
        },
        {
            Direction::North, Direction::South
        },
    },

    {
        {
            Direction::North, Direction::East
        },
        {
            Direction::East, Direction::South
        },
        {
            Direction::South, Direction::West
        },
        {
            Direction::West, Direction::North
        }
    },

    {
        {
            Direction::West, Direction::North, Direction::East
        },
        {
            Direction::North, Direction::East, Direction::South
        },
        {
            Direction::East, Direction::South, Direction::West
        },
        {
            Direction::South, Direction::West, Direction::North
        }
    },

    {
        {
            Direction::North, Direction::East, Direction::South, Direction::West
        },
    }
};

static int sRowSize;
static int sColSize;

static unsigned int sMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
static unsigned int sMinBlindSpots = UINT_MAX;

static void UpdateDetectionsOnMap(const Position& cameraStartPosition, const std::vector<Direction>& rotatedCameraDirections, unsigned int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    for (const Direction detectDirection : rotatedCameraDirections)
    {
        const Position& detectPosition = DETECT_POSITIONS[static_cast<unsigned int>(detectDirection)];

        int nextRow = cameraStartPosition.Row;
        int nextCol = cameraStartPosition.Col;
        
        while (true)
        {
            nextRow += detectPosition.Row;
            nextCol += detectPosition.Col;

            if (nextRow < 0 || nextRow >= sRowSize || nextCol < 0 || nextCol >= sColSize)
            {
                break;
            }

            if (map[nextRow][nextCol] == WALL)
            {
                break;
            }

            if (map[nextRow][nextCol] != EMPTY)
            {
                continue;
            }

            map[nextRow][nextCol] = DETECTION;
        }
    }
}

static unsigned int GetBlindSpots(unsigned int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    unsigned int count = 0;

    for (int row = 0; row < sRowSize; ++row)
    {
        for (int col = 0; col < sColSize; ++col)
        {
            if (map[row][col] == EMPTY)
            {
                ++count;
            }
        }
    }

    return count;
}

static void GetMinBlindSpotsRecursive(unsigned int nextCameraIndex, const std::vector<Camera>& cameras, unsigned int map[MAX_MAP_SIZE][MAX_MAP_SIZE])
{
    if (nextCameraIndex == cameras.size())
    {
        unsigned int blindSpots = GetBlindSpots(map);
        
        if (blindSpots < sMinBlindSpots)
        {
            sMinBlindSpots = blindSpots;
        }

        return;
    }

    const Camera& camera = cameras[nextCameraIndex];
    for (const std::vector<Direction>& rotatedCameraDirections : CAMERA_DETECT_DIRECTIONS[camera.Type])
    {
        unsigned int copiedMap[MAX_MAP_SIZE][MAX_MAP_SIZE];
        memcpy(copiedMap, map, sizeof(copiedMap));

        UpdateDetectionsOnMap(camera.Pos, rotatedCameraDirections, copiedMap);

        GetMinBlindSpotsRecursive(nextCameraIndex + 1, cameras, copiedMap);
    }
}

int main()
{
    std::cin >> sRowSize >> sColSize;
    
    std::vector<Camera> cameras;
    for (int row = 0; row < sRowSize; ++row)
    {
        for (int col = 0; col < sColSize; ++col)
        {
            std::cin >> sMap[row][col];

            unsigned int state = sMap[row][col];
            if (state == EMPTY || state == WALL)
            {
                continue;
            }

            Camera camera;
            camera.Pos = { row, col };
            camera.Type = state - 1;

            cameras.push_back(std::move(camera));
        }
    }

    GetMinBlindSpotsRecursive(0, cameras, sMap);
    std::cout << sMinBlindSpots;

    return 0;
}