#include <iostream>
#include <set>

#define MAX_STRING_ROAD_SIZE (8U)
#define MAX_MAP_SIZE (101)
#define MAX_MOVE_POSITIONS_SIZE (2)


static long long sCases[MAX_MAP_SIZE][MAX_MAP_SIZE] = { 0, };
static std::set<std::pair<std::pair<unsigned int, unsigned int>, std::pair<unsigned int, unsigned int>>> sRepairRoads;

int main()
{
    unsigned int mapSizeX;
    unsigned int mapSizeY;
    std::cin >> mapSizeX >> mapSizeY;
    mapSizeX++;
    mapSizeY++;

    unsigned int repairRoadsCount;
    std::cin >> repairRoadsCount;

    for (unsigned int i = 0; i < repairRoadsCount; ++i)
    {
        unsigned int startX;
        unsigned int startY;
        std::cin >> startX >> startY;
        
        unsigned int endX;
        unsigned int endY;
        std::cin >> endX >> endY;

        sRepairRoads.insert({ { startX, startY }, { endX, endY } });
        sRepairRoads.insert({ { endX, endY }, { startX, startY } });
    }

    sCases[0][0] = 1;
    for (unsigned int y = 0; y < mapSizeY; ++y)
    {
        for (unsigned int x = 0; x < mapSizeX; ++x)
        {
            if (x < (mapSizeX - 1) && sRepairRoads.find({ { x, y }, { x + 1, y } }) == sRepairRoads.end())
            {
                sCases[y][x + 1] += sCases[y][x];
            }

            if (y < (mapSizeY - 1) && sRepairRoads.find({ { x, y }, { x, y + 1 } }) == sRepairRoads.end())
            {
                sCases[y + 1][x] += sCases[y][x];
            }
        }
    }

    std::cout << sCases[mapSizeY - 1][mapSizeX - 1];

    return 0;
}