
#include <cassert>
#include <climits>
#include <iostream>
#include <string>

#define MAX_BLOCK_COUNT (1000)

static unsigned int sEnergies[MAX_BLOCK_COUNT] = { 0, };

int main()
{
    unsigned int blockCount = 0;
    std::cin >> blockCount;

    std::string blocks;
    std::cin >> blocks;

    for (unsigned int i = 0; i < MAX_BLOCK_COUNT; ++i)
    {
        sEnergies[i] = UINT_MAX;
    }

    sEnergies[0] = 0;
    for (unsigned int i = 0; i < blockCount; ++i)
    {
        if (sEnergies[i] == UINT_MAX)
        {
            continue;
        }

        for (unsigned int j = i + 1; j < blockCount; ++j)
        {
            unsigned int usedEnergy = (j - i) * (j - i);

            switch (blocks[i])
            {
            case 'B':
                if (blocks[j] == 'O')
                {
                    sEnergies[j] = std::min(sEnergies[j], sEnergies[i] + usedEnergy);
                }

                break;
            case 'O':
                if (blocks[j] == 'J')
                {
                    sEnergies[j] = std::min(sEnergies[j], sEnergies[i] + usedEnergy);
                }

                break;
            case 'J':
                if (blocks[j] == 'B')
                {
                    sEnergies[j] = std::min(sEnergies[j], sEnergies[i] + usedEnergy);
                }

                break;
            default:
                assert(false);
            }
        }
    }

    if (blockCount == 1 || sEnergies[blockCount - 1] == UINT_MAX)
    {
        std::cout << "-1";
    }
    else
    {
        std::cout << sEnergies[blockCount - 1];
    }

    return 0;
}
