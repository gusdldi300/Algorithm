
#include <iostream>
#include <vector>

int main()
{
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
    unsigned int deleteCount = 0;

    unsigned int startIndex = 0;
    for (unsigned int endIndex = 0; endIndex < numbersCount; ++endIndex)
    {
        if (numbers[endIndex] % 2 == 0)
        {
            continuosEvenNumbersCount++;

            maxContinuosEvenNumbersCount = std::max(maxContinuosEvenNumbersCount, continuosEvenNumbersCount);

            continue;
        }

        if (deleteCount < totalDeleteCount)
        {
            deleteCount++;

            continue;
        }

        for (startIndex; startIndex <= endIndex; ++startIndex)
        {
            if (numbers[startIndex] % 2 != 0)
            {
                startIndex++;

                break;
            }

            continuosEvenNumbersCount--;
        }

    }

    std::cout << maxContinuosEvenNumbersCount;

    return 0;
}