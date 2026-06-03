#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

#define MAX_NUMBERS_COUNT (2001U)

int main()
{
    std::cin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    unsigned int numbersCount;
    std::cin >> numbersCount;

    bool bZero = false;
    std::vector<long long> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        long long number;
        std::cin >> number;

        numbers.push_back(number);
    }

    std::sort(numbers.begin(), numbers.end());

    unsigned int goodsCount = 0;

    for (unsigned int targetNumberIndex = 0; targetNumberIndex < numbers.size(); ++targetNumberIndex)
    {
        for (unsigned int firstNumberIndex = 0; firstNumberIndex < numbers.size(); ++firstNumberIndex)
        {
            if (firstNumberIndex == targetNumberIndex)
            {
                continue;
            }

            long long secondNumber = numbers[targetNumberIndex] - numbers[firstNumberIndex];
            
            std::vector<long long>::iterator startFoundIter = std::lower_bound(numbers.begin(), numbers.end(), secondNumber);
            std::vector<long long>::iterator endFoundIter = std::upper_bound(numbers.begin(), numbers.end(), secondNumber);

            long long count = static_cast<long long>(endFoundIter - startFoundIter);
            if (secondNumber == numbers[firstNumberIndex])
            {
                count--;
            }

            if (secondNumber == numbers[targetNumberIndex])
            {
                count--;
            }

            if (count > 0)
            {
                ++goodsCount;

                break;
            }
        }
    }

    std::cout << goodsCount;

    return 0;
}