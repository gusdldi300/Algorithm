
#include <iostream>
#include <cstring>

#define MAX_NUMBERS_COUNT (11U)
#define MAX_NUMBER (2001U)

unsigned long long GetBuyCountRecursive(unsigned int leftCount, unsigned int number, const unsigned int maxNumber, unsigned long long buyCounts[][MAX_NUMBER])
{
    if (leftCount == 0)
    {
        return 1;
    }

    if (number > maxNumber)
    {
        return 0;
    }

    if (buyCounts[leftCount][number] > 0)
    {
        return buyCounts[leftCount][number];
    }

    unsigned long long totalBuyCount = 0;
    for (unsigned int nextNumber = number; nextNumber <= maxNumber; ++nextNumber)
    {
        unsigned long long buyCount = GetBuyCountRecursive(leftCount - 1, nextNumber * 2, maxNumber, buyCounts);
        if (buyCount == 0)
        {
            break;
        }

        totalBuyCount += buyCount;
    }

    buyCounts[leftCount][number] = totalBuyCount;

    return totalBuyCount;
}

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int testsCount;
    std::cin >> testsCount;

    unsigned long long buyCounts[MAX_NUMBERS_COUNT][MAX_NUMBER];

    for (unsigned int i = 0; i < testsCount; ++i)
    {
        unsigned int numbersCount;
        unsigned int maxNumber;

        std::cin >> numbersCount >> maxNumber;
        memset(buyCounts, 0, sizeof(buyCounts));

        std::cout << GetBuyCountRecursive(numbersCount, 1, maxNumber, buyCounts) << '\n';
    }

    return 0;
}