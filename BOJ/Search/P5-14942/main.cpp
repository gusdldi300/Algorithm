#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <unordered_set>

#define MAX_ROOMS_COUNT (101U)
#define MAX_MOVE_COUNT (17U)

static unsigned int sRoomsCount = 0;
static unsigned int sMovesSize = 0;

static std::pair<unsigned int, unsigned int> sNextRoomMovedEnergies[MAX_MOVE_COUNT][MAX_ROOMS_COUNT];
static std::unordered_map<unsigned int, unsigned int> sRoomGraph[MAX_ROOMS_COUNT];

static std::unordered_set<unsigned int> sVisited;

static void SetFirstMovesFromRoomGraphRecursive(unsigned int room)
{
    sVisited.insert(room);

    for (const auto& childRoom : sRoomGraph[room])
    {
        if (sVisited.find(childRoom.first) != sVisited.end())
        {
            sNextRoomMovedEnergies[0][room] = childRoom;

            continue;
        }

        SetFirstMovesFromRoomGraphRecursive(childRoom.first);
    }
}

unsigned int GetClosestRoomRecursive(unsigned int room, unsigned long long energy)
{
    if (room <= 1)
    {
        return 1;
    }

    if (energy < sNextRoomMovedEnergies[0][room].second)
    {
        return room;
    }

    for (unsigned int moveIndex = 1; moveIndex < sMovesSize; ++moveIndex)
    {
        if (energy < sNextRoomMovedEnergies[moveIndex][room].second)
        {
            return GetClosestRoomRecursive(sNextRoomMovedEnergies[moveIndex - 1][room].first, energy - sNextRoomMovedEnergies[moveIndex - 1][room].second);
        }
    }

    return 1;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    std::cin >> sRoomsCount;
    
    std::vector<unsigned long long> antEnergies;
    for (unsigned int i = 0; i < sRoomsCount; ++i)
    {
        unsigned long long energy;
        std::cin >> energy;

        antEnergies.push_back(energy);
    }

    for (unsigned int i = 0; i < sRoomsCount - 1; ++i)
    {
        unsigned int endRoom;
        unsigned int startRoom;

        unsigned long long energy;

        std::cin >> startRoom >> endRoom >> energy;

        sRoomGraph[startRoom].insert(std::pair<unsigned int, unsigned int>(endRoom, energy));
        sRoomGraph[endRoom].insert(std::pair<unsigned int, unsigned int>(startRoom, energy));
    }

    SetFirstMovesFromRoomGraphRecursive(1);

    unsigned int moveCount = 1;
    while (moveCount < sRoomsCount)
    {
        sMovesSize++;

        moveCount *= 2;
    }

    for (unsigned int moveIndex = 1; moveIndex < sMovesSize; ++moveIndex)
    {
        for (unsigned int room = 1; room <= sRoomsCount; room++)
        {
            const std::pair<unsigned int, unsigned long long>& lastRoomMovedEnergy = sNextRoomMovedEnergies[moveIndex - 1][room];
            const std::pair<unsigned int, unsigned long long>& nextRoomMovedEnergy = sNextRoomMovedEnergies[moveIndex - 1][lastRoomMovedEnergy.first];

            unsigned int nextRoom = nextRoomMovedEnergy.first;
            unsigned long long movedEnergy = nextRoomMovedEnergy.second + lastRoomMovedEnergy.second;

            sNextRoomMovedEnergies[moveIndex][room] = std::pair<unsigned int, unsigned long long>(nextRoom, movedEnergy);
        }
    }

    for (unsigned int room = 1; room <= sRoomsCount; ++room)
    {
        std::cout << GetClosestRoomRecursive(room, antEnergies[room - 1]) << '\n';
    }

    return 0;
}