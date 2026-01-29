
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_NUMBERS_COUNT (1001U)

static void GetContinuosSumsOf(const std::vector<int>& numbers, std::vector<int>* outContinuosSums)
{
    for (unsigned int startIndex = 0; startIndex < numbers.size(); ++startIndex)
    {
        int sum = numbers[startIndex];

        for (unsigned int addIndex = startIndex + 1; addIndex < numbers.size(); ++addIndex)
        {
            outContinuosSums->push_back(sum);

            sum += numbers[addIndex];
        }
        
        outContinuosSums->push_back(sum);
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
    GetContinuosSumsOf(firstNumbers, &firstContinuosSums);

    std::vector<int> secondContinuosSumsAscend;
    GetContinuosSumsOf(secondNumbers, &secondContinuosSumsAscend);

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