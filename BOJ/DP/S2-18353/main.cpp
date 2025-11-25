
#include <iostream>
#include <algorithm>

#define MAX_SOLDIER_COUNT (2000U)

static int sSoldierCounts[MAX_SOLDIER_COUNT] = { 0, };
static int sSoldiers[MAX_SOLDIER_COUNT] = { 0, };

int main()
{
    int soldierCount = 0;
    std::cin >> soldierCount;
    
    sSoldierCounts[0] = 1;
    std::cin >> sSoldiers[0];

    int maxSoldierCount = sSoldierCounts[0];
    for (int i = 1; i < soldierCount; ++i)
    {
        std::cin >> sSoldiers[i];

        for (int j = i - 1; j >= 0; --j)
        {
            if (sSoldiers[i] < sSoldiers[j])
            {
                sSoldierCounts[i] = std::max(sSoldierCounts[i], sSoldierCounts[j]);
            }
        }

        sSoldierCounts[i]++;

        if (sSoldierCounts[i] > maxSoldierCount)
        {
            maxSoldierCount = sSoldierCounts[i];
        }
    }

    std::cout << (soldierCount - maxSoldierCount);

    return 0;
}