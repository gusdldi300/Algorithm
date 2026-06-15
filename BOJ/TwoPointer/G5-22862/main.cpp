
#include <iostream>
#include <vector>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int numbersCount;
    unsigned int totalDeleteCount;

    std::cin >> numbersCount >> totalDeleteCount;

    std::vector<unsigned int> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        numbers.push_back(number);
    }

    unsigned int maxContinuosEvenNumbersCount = 0;
    unsigned int continuosEvenNumbersCount = 0;
    unsigned int leftDeleteCount = totalDeleteCount;

    unsigned int rightIndex = 0;
    for (unsigned int leftIndex = 0; leftIndex < numbersCount; ++leftIndex)
    {
        while (true)
        {
            if (rightIndex == numbersCount)
            {
                goto OUTER;
            }

            if (numbers[rightIndex] % 2 != 0)
            {
                if (leftDeleteCount == 0)
                {
                    break;
                }

                --leftDeleteCount;
            }
            else
            {
                ++continuosEvenNumbersCount;
                
                maxContinuosEvenNumbersCount = std::max(maxContinuosEvenNumbersCount, continuosEvenNumbersCount);
            }

            ++rightIndex;
        }

        if (numbers[leftIndex] % 2 != 0)
        {
            ++leftDeleteCount;
        }
        else
        {
            --continuosEvenNumbersCount;
        }
    }

OUTER:
    std::cout << maxContinuosEvenNumbersCount;

    return 0;
}