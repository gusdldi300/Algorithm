
#include <algorithm>
#include <climits>
#include <iostream>

#define MAX_ENERGY (5000U)
#define MAX_STONE_COUNT (20U)

#define SUPER_JUMP (3U)
#define LOW_JUMP (1U)
#define HIGH_JUMP (2U)

struct Energy
{
    unsigned int low;
    unsigned int high;
};

static Energy sJumpEnergies[MAX_STONE_COUNT] = { 0, };
static unsigned int sUsedEnergies[MAX_STONE_COUNT][2] = { 0, };

int main()
{
    unsigned int stoneCount = 0;
    std::cin >> stoneCount;

    for (unsigned int stone = 0; stone < stoneCount - 1; ++stone)
    {
        std::cin >> sJumpEnergies[stone].low >> sJumpEnergies[stone].high;
    }

    unsigned int superJumpEnergy = 0;
    std::cin >> superJumpEnergy;

    for (unsigned int stone = 1; stone < stoneCount; ++stone)
    {
        sUsedEnergies[stone][0] = MAX_ENERGY;
        sUsedEnergies[stone][1] = MAX_ENERGY;
    }

    sUsedEnergies[1][0] = sJumpEnergies[0].low;
    sUsedEnergies[2][0] = std::min(sUsedEnergies[1][0] + sJumpEnergies[1].low, sJumpEnergies[0].high);

    for (int stone = SUPER_JUMP; stone < stoneCount; ++stone)
    {
        unsigned int lowJumpIndex = stone - LOW_JUMP;
        unsigned int highJumpIndex = stone - HIGH_JUMP;

        sUsedEnergies[stone][0] = std::min(sUsedEnergies[lowJumpIndex][0] + sJumpEnergies[lowJumpIndex].low,
                                            sUsedEnergies[highJumpIndex][0] + sJumpEnergies[highJumpIndex].high);

        sUsedEnergies[stone][1] = std::min(sUsedEnergies[lowJumpIndex][1] + sJumpEnergies[lowJumpIndex].low,
            sUsedEnergies[highJumpIndex][1] + sJumpEnergies[highJumpIndex].high);
        sUsedEnergies[stone][1] = std::min(sUsedEnergies[stone][1], sUsedEnergies[stone - SUPER_JUMP][0] + superJumpEnergy);
    }

    unsigned int minUsedEnergy = std::min(sUsedEnergies[stoneCount - 1][0], sUsedEnergies[stoneCount - 1][1]);
    std::cout << minUsedEnergy;

    return 0;
}