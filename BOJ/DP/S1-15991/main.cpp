
#include <iostream>

#define MAX_SUM_NUMBER (100001)
#define MAX_USABLE_NUMBER (3)

#define DIVISOR (1000000009)

static unsigned int sSymmetricSumCounts[MAX_SUM_NUMBER] = { 0, };

int main()
{
    sSymmetricSumCounts[0] = 1;

    sSymmetricSumCounts[1] = 1;
    sSymmetricSumCounts[2] = 2;
    sSymmetricSumCounts[3] = 2;

    for (int sum = 4; sum < MAX_SUM_NUMBER; ++sum)
    {
        for (int usableNumber = 1; usableNumber <= MAX_USABLE_NUMBER; ++usableNumber)
        {
            int checkNumber = (sum - (2 * usableNumber));
            if (checkNumber < 0)
            {
                continue;
            }

            sSymmetricSumCounts[sum] = (sSymmetricSumCounts[sum] + sSymmetricSumCounts[checkNumber]) % DIVISOR;
        }
    }

    unsigned int testCount = 0;
    std::cin >> testCount;

    for (unsigned int test = 0; test < testCount; ++test)
    {
        unsigned int targetSum = 0;
        std::cin >> targetSum;

        std::cout << sSymmetricSumCounts[targetSum] << std::endl;
    }

    return 0;
}