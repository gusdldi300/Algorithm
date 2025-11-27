
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>

#define MAX_DISTANCE (10001U)
#define MAX_SHORTCUTS (12U)

struct Shortcut
{
    unsigned int Start;
    unsigned int End;

    unsigned int Distance;
};

static unsigned int sMinDriveDistances[MAX_DISTANCE] = { 0, };

int main()
{
    unsigned int shortcutsCount = 0;
    unsigned int highwayDistance = 0;

    std::cin >> shortcutsCount >> highwayDistance;

    std::unordered_map<unsigned int, std::vector<Shortcut>> shortcuts;
    
    shortcuts.reserve(shortcutsCount);
    for (unsigned int i = 0; i < shortcutsCount; ++i)
    {
        Shortcut shortcut;
        std::cin >> shortcut.Start >> shortcut.End >> shortcut.Distance;

        shortcuts[shortcut.End].push_back(shortcut);
    }

    for (unsigned int distance = 1; distance <= highwayDistance; ++distance)
    {
        unsigned int minDistance = sMinDriveDistances[distance - 1] + 1;

        std::unordered_map<unsigned int, std::vector<Shortcut>>::iterator shortcutsIter = shortcuts.find(distance);
        if (shortcutsIter != shortcuts.end())
        {
            for (Shortcut shortcut : shortcutsIter->second)
            {
                minDistance = std::min(minDistance, sMinDriveDistances[shortcut.Start] + shortcut.Distance);
            }
        }

        sMinDriveDistances[distance] = minDistance;
    }

    std::cout << sMinDriveDistances[highwayDistance];

    return 0;
}