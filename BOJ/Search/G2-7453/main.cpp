
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_ARRAYS_COUNT (4U)
#define MAX_NUMBERS_COUNT (4001U)

int main()
{
    unsigned int numbersCount;
    std::cin >> numbersCount;

    int numberArrays[MAX_ARRAYS_COUNT][MAX_NUMBERS_COUNT] = { 0, };
    for (unsigned int numbersIndex = 0; numbersIndex < numbersCount; ++numbersIndex)
    {
        for (unsigned int arrayIndex = 0; arrayIndex < MAX_ARRAYS_COUNT; ++arrayIndex)
        {
            std::cin >> numberArrays[arrayIndex][numbersIndex];
        }
    }
    
    std::vector<int> firstMixedArray;
    std::vector<int> secondMixedArray;

    for (unsigned int numbersIndex = 0; numbersIndex < numbersCount; ++numbersIndex)
    {
        for (unsigned int addNumbersIndex = 0; addNumbersIndex < numbersCount; ++addNumbersIndex)
        {
            firstMixedArray.push_back(numberArrays[0][numbersIndex] + numberArrays[1][addNumbersIndex]);
            secondMixedArray.push_back(numberArrays[2][numbersIndex] + numberArrays[3][addNumbersIndex]);
        }
    }

    std::sort(firstMixedArray.begin(), firstMixedArray.end());
    std::sort(secondMixedArray.begin(), secondMixedArray.end());

    long long count = 0; // Max: 4000^4
    for (unsigned int numbersIndex = 0; numbersIndex < firstMixedArray.size(); ++numbersIndex)
    {
        int firstMixedNumber = firstMixedArray[numbersIndex];

        auto lowerIter = std::lower_bound(secondMixedArray.begin(), secondMixedArray.end(), firstMixedNumber * -1);
        auto upperIter = std::upper_bound(secondMixedArray.begin(), secondMixedArray.end(), firstMixedNumber * -1);

        count += (static_cast<long long>(upperIter - lowerIter));
    }

    std::cout << count;

    return 0;
}