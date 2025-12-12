
#include <iostream>

#define MAX_STATUES_COUNT (1000001U)

#define LEFT_SIGHT_INDEX (0U)
#define RIGHT_SIGHT_INDEX (1U)

static unsigned int sEnlightments[2][MAX_STATUES_COUNT] = { 0, };

int main()
{
    unsigned int statuesCount;
    std::cin >> statuesCount;

    static unsigned int sEnlightments[2][MAX_STATUES_COUNT] = { 0, };
    for (unsigned int i = 0; i < statuesCount; ++i)
    {
        unsigned int sight;
        std::cin >> sight;

        unsigned int lastStatue = i;
        unsigned int statue = i + 1;
        
        if (sight == (LEFT_SIGHT_INDEX + 1))
        {
            sEnlightments[LEFT_SIGHT_INDEX][statue] = sEnlightments[LEFT_SIGHT_INDEX][lastStatue] + 1;
            sEnlightments[RIGHT_SIGHT_INDEX][statue] =
                ((sEnlightments[RIGHT_SIGHT_INDEX][lastStatue] > 0) ? sEnlightments[RIGHT_SIGHT_INDEX][lastStatue] - 1 : 0);
        }
        else
        {
            sEnlightments[RIGHT_SIGHT_INDEX][statue] = sEnlightments[RIGHT_SIGHT_INDEX][lastStatue] + 1;
            sEnlightments[LEFT_SIGHT_INDEX][statue] =
                ((sEnlightments[LEFT_SIGHT_INDEX][lastStatue] > 0) ? sEnlightments[LEFT_SIGHT_INDEX][lastStatue] - 1 : 0);
        }
    }

    unsigned int maxEnlightment = 0;
    for (unsigned int i = 1; i <= statuesCount; ++i)
    {
        maxEnlightment = std::max(maxEnlightment, sEnlightments[RIGHT_SIGHT_INDEX][i]);
        maxEnlightment = std::max(maxEnlightment, sEnlightments[LEFT_SIGHT_INDEX][i]);
    }

    std::cout << maxEnlightment;

    return 0;
}