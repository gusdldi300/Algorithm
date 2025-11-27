
#include <algorithm>
#include <iostream>
#include <vector>

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

    std::vector<Shortcut> shortcuts;
    shortcuts.reserve(shortcutsCount);
    for (unsigned int i = 0; i < shortcutsCount; ++i)
    {
        Shortcut shortcut;
        std::cin >> shortcut.Start >> shortcut.End >> shortcut.Distance;

        shortcuts.push_back(shortcut);
    }

    for (unsigned int distance = 1; distance <= highwayDistance; ++distance)
    {
        unsigned int minDistance = sMinDriveDistances[distance - 1] + 1;

        for (Shortcut shortcut : shortcuts)
        {
            if (shortcut.End == distance)
            {
                minDistance = std::min(minDistance, sMinDriveDistances[shortcut.Start] + shortcut.Distance);
            }
        }

        sMinDriveDistances[distance] = minDistance;
    }

    std::cout << sMinDriveDistances[highwayDistance];

    return 0;
}