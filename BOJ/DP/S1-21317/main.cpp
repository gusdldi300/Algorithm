
#include <algorithm>
#include <climits>
#include <iostream>

#define MAX_STONE_COUNT (21U)

#define SUPER_JUMP (3)
#define LOW_JUMP (1)
#define HIGH_JUMP (2)

struct Energy
{
    unsigned int low;
    unsigned int high;
};

static Energy sJumpEnergies[MAX_STONE_COUNT] = { 0, };
static unsigned int sUsedEnergies[MAX_STONE_COUNT][MAX_STONE_COUNT] = { 0, };

int main()
{
    int stoneCount = 0;
    std::cin >> stoneCount;

    for (int stone = 1; stone < stoneCount; ++stone)
    {
        std::cin >> sJumpEnergies[stone].low >> sJumpEnergies[stone].high;
    }
    
    unsigned int superJumpEnergy = 0;
    std::cin >> superJumpEnergy;

    if (stoneCount == 1)
    {
        std::cout << 0;

        return 0;
    }
    else if (stoneCount == 2)
    {
        std::cout << sJumpEnergies[stoneCount - 1].low;

        return 0;
    }

    for (int superJumpIndex = 0; superJumpIndex <= stoneCount - SUPER_JUMP; ++superJumpIndex)
    {
        for (int stone = 2; stone <= stoneCount; ++stone)
        {
            sUsedEnergies[superJumpIndex][stone] = UINT_MAX;
        }
    }

    for (int superJumpIndex = 0; superJumpIndex <= stoneCount - SUPER_JUMP; ++superJumpIndex)
    {
        int stone = 1;
        for (stone = 1; stone <= stoneCount; ++stone)
        {
            if (superJumpIndex == stone)
            {
                stone += SUPER_JUMP;

                sUsedEnergies[superJumpIndex][stone] = sUsedEnergies[superJumpIndex][stone - SUPER_JUMP] + superJumpEnergy;
            }

            if (stone + HIGH_JUMP <= stoneCount)
            {
                sUsedEnergies[superJumpIndex][stone + HIGH_JUMP] = sUsedEnergies[superJumpIndex][stone] + sJumpEnergies[stone].high;
            }

            if (stone + LOW_JUMP <= stoneCount)
            {
                sUsedEnergies[superJumpIndex][stone + LOW_JUMP] = std::min(sUsedEnergies[superJumpIndex][stone] + sJumpEnergies[stone].low, sUsedEnergies[superJumpIndex][stone + LOW_JUMP]);
            }
        }
    }

    unsigned int minUsedEnergy = UINT_MAX;
    for (int superJumpIndex = 0; superJumpIndex <= stoneCount - SUPER_JUMP; ++superJumpIndex)
    {
        minUsedEnergy = std::min(minUsedEnergy, sUsedEnergies[superJumpIndex][stoneCount]);
    }

    std::cout << minUsedEnergy;

    return 0;
}