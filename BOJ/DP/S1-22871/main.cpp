
#include <algorithm>
#include <cstdlib>
#include <climits>
#include <iostream>

#define MAX_STONE_COUNT (5000U)

static long long sUsedEnergies[MAX_STONE_COUNT] = { 0, };
static int sStones[MAX_STONE_COUNT] = { 0, };

int main()
{
    unsigned int stoneCount = 0;
    std::cin >> stoneCount;

    for (unsigned int stone = 0; stone < stoneCount; ++stone)
    {
        std::cin >> sStones[stone];
        sUsedEnergies[stone] = LLONG_MAX;
    }

    long long minEnergy = LLONG_MAX;

    sUsedEnergies[0] = 0;
    for (unsigned int curStone = 0; curStone < stoneCount; ++curStone)
    {
        for (unsigned int nextStone = curStone + 1; nextStone < stoneCount; ++nextStone)
        {
            long long energy = (nextStone - curStone) * (1 + abs(sStones[curStone] - sStones[nextStone]));
            sUsedEnergies[nextStone] = std::min(sUsedEnergies[nextStone], std::max(sUsedEnergies[curStone], energy));
        }
    }

    std::cout << sUsedEnergies[stoneCount - 1];

    return 0;
}