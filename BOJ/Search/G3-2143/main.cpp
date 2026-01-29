
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NUMBERS_COUNT (1001U)

static void SetContinuosSumsOf(const std::vector<int>& numbers, std::vector<int>* outContinuosSums)
{
    *outContinuosSums = numbers;

    unsigned int lastStartIndex = 0;
    for (unsigned int continuousCount = 2; continuousCount <= numbers.size(); ++continuousCount)
    {
        unsigned int addIndex = continuousCount - 1;

        unsigned int lastSumsSize = outContinuosSums->size() - 1;
        for (unsigned int lastIndex = lastStartIndex; lastIndex < lastSumsSize; ++lastIndex)
        {
            unsigned int lastNumber = (*outContinuosSums)[lastIndex];

            outContinuosSums->push_back(lastNumber + numbers[addIndex]);

            ++addIndex;
        }

        lastStartIndex = lastSumsSize + 1;
    }
}

int main()
{
    int targetNumber;
    std::cin >> targetNumber;

    unsigned int firstNumbersCount;
    std::cin >> firstNumbersCount;

    std::vector<int> firstNumbers;
    for (unsigned int i = 0; i < firstNumbersCount; ++i)
    {
        int number;
        std::cin >> number;

        firstNumbers.push_back(number);
    }

    unsigned int secondNumbersCount;
    std::cin >> secondNumbersCount;

    std::vector<int> secondNumbers;
    for (unsigned int i = 0; i < secondNumbersCount; ++i)
    {
        int number;
        std::cin >> number;

        secondNumbers.push_back(number);
    }

    std::vector<int> firstContinuosSums;
    SetContinuosSumsOf(firstNumbers, &firstContinuosSums);

    std::vector<int> secondContinuosSumsAscend;
    SetContinuosSumsOf(secondNumbers, &secondContinuosSumsAscend);

    std::sort(secondContinuosSumsAscend.begin(), secondContinuosSumsAscend.end());

    unsigned long long foundCount = 0;
    for (int number : firstContinuosSums)
    {
        int searchNumber = targetNumber - number;

        auto foundStartIter = std::lower_bound(secondContinuosSumsAscend.begin(), secondContinuosSumsAscend.end(), searchNumber);
        if (foundStartIter != secondContinuosSumsAscend.end() && (*foundStartIter) == searchNumber)
        {
            auto foundEndIter = std::upper_bound(secondContinuosSumsAscend.begin(), secondContinuosSumsAscend.end(), searchNumber);

            foundCount += (static_cast<unsigned long long>(foundEndIter - foundStartIter));
        }
    }

    std::cout << foundCount;

    return 0;
}