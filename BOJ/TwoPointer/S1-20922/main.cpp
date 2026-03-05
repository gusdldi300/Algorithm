
#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    unsigned int numbersCount;
    unsigned int maxDuplicateCount;

    std::cin >> numbersCount >> maxDuplicateCount;

    std::vector<unsigned int> numbers;
    std::unordered_map<unsigned int, unsigned int> numberDuplicateCountMap;

    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        numbers.push_back(number);

        numberDuplicateCountMap[number] = 0;
    }

    unsigned int maxContinuosCount = 0;

    unsigned int continuosCount = 0;
    unsigned int leftIndex = 0;
    unsigned int rightIndex = 0;

    while (rightIndex < numbersCount)
    {
        unsigned int rightNumber = numbers[rightIndex];

        if (numberDuplicateCountMap[rightNumber] < maxDuplicateCount)
        {
            ++numberDuplicateCountMap[rightNumber];
            ++continuosCount;

            maxContinuosCount = std::max(maxContinuosCount, continuosCount);

            ++rightIndex;

            continue;
        }

        while (leftIndex < rightIndex)
        {
            unsigned int leftNumber = numbers[leftIndex];

            --numberDuplicateCountMap[leftNumber];
            --continuosCount;
            ++leftIndex;

            if (leftNumber == rightNumber)
            {
                break;
            }
        }
    }

    std::cout << maxContinuosCount;

    return 0;
}