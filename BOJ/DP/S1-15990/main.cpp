
#include <iostream>

#define MAX_SUM_NUMBER (100001U)
#define MAX_USABLE_NUMBERS (3U)
#define DIVISOR (1000000009U)

static unsigned int sSumLeftMostCounts[MAX_SUM_NUMBER][MAX_USABLE_NUMBERS + 1] = { 0, };

int main()
{
    unsigned int testCount = 0;
    std::cin >> testCount;

    sSumLeftMostCounts[1][1] = 1;
    sSumLeftMostCounts[2][2] = 1;

    sSumLeftMostCounts[3][1] = 1;
    sSumLeftMostCounts[3][2] = 1;
    sSumLeftMostCounts[3][3] = 1;

    for (unsigned int sum = 4; sum < MAX_SUM_NUMBER; ++sum)
    {
        sSumLeftMostCounts[sum][1] = (sSumLeftMostCounts[sum - 1][2] + sSumLeftMostCounts[sum - 1][3]) % DIVISOR; 
        sSumLeftMostCounts[sum][2] = (sSumLeftMostCounts[sum - 2][1] + sSumLeftMostCounts[sum - 2][3]) % DIVISOR;
        sSumLeftMostCounts[sum][3] = (sSumLeftMostCounts[sum - 3][1] + sSumLeftMostCounts[sum - 3][2]) % DIVISOR;
    }

    for (unsigned int test = 0; test < testCount; ++test)
    {
        unsigned int targetSumNumber = 0;
        std::cin >> targetSumNumber;

        std::cout << ((sSumLeftMostCounts[targetSumNumber][1] + sSumLeftMostCounts[targetSumNumber][2] + sSumLeftMostCounts[targetSumNumber][3]) % DIVISOR)
            << std::endl;
    }

    return 0;
}