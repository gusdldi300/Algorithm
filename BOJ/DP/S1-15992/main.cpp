

#include <iostream>

#define MAX_SUM_NUMBER (1001U)
#define MAX_USED_COUNT (MAX_SUM_NUMBER)
#define MAX_USABLE_NUMBER (3U)

#define DIVISOR (1000000009U)

static unsigned int sUsedCounts[MAX_SUM_NUMBER][MAX_USED_COUNT] = { 0, };

int main()
{
    sUsedCounts[1][1] = 1;
    
    sUsedCounts[2][1] = 1;
    sUsedCounts[2][2] = 1;

    sUsedCounts[3][1] = 1;
    sUsedCounts[3][2] = 2;
    sUsedCounts[3][3] = 1;

    for (unsigned int sum = 4; sum < MAX_SUM_NUMBER; ++sum)
    {
        for (unsigned int usedCount = 2; usedCount <= sum; ++usedCount)
        {
            for (unsigned int usableNumber = 1; usableNumber <= MAX_USABLE_NUMBER; ++usableNumber)
            {
                sUsedCounts[sum][usedCount] = (sUsedCounts[sum][usedCount] + sUsedCounts[sum - usableNumber][usedCount - 1]) % DIVISOR;
            }
        }
    }

    unsigned int testCount = 0;
    std::cin >> testCount;

    for (unsigned int test = 0; test < testCount; ++test)
    {
        unsigned int targetSum = 0;
        unsigned int targetUsedCount = 0;
        std::cin >> targetSum >> targetUsedCount;

        std::cout << sUsedCounts[targetSum][targetUsedCount] << std::endl;
    }

    return 0;
}