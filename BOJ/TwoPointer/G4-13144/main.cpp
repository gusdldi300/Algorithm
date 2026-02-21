#include <iostream>
#include <vector>
#include <unordered_map>

int main()
{
    unsigned int numbersCount;
    std::cin >> numbersCount;
    
    std::unordered_map<unsigned int, unsigned int> numberCountMap;
    
    std::vector<unsigned int> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        numbers.push_back(number);
        numberCountMap[number] = 0;
    }

    unsigned long long uniqueNumbersCount = 0;

    unsigned long long casesCount = 0;
    unsigned int startIndex = 0;
    for (unsigned int endIndex = 0; endIndex < numbersCount; ++endIndex)
    {
        unsigned int endNumber = numbers[endIndex];
        uniqueNumbersCount++;

        if (numberCountMap[endNumber] == 0)
        {
            numberCountMap[endNumber] = 1;
            casesCount += uniqueNumbersCount;

            continue;
        }

        numberCountMap[endNumber]++;

        for (startIndex; startIndex < numbersCount; ++startIndex)
        {
            if (numberCountMap[endNumber] == 1)
            {
                casesCount += uniqueNumbersCount;

                break;
            }

            numberCountMap[numbers[startIndex]]--;
            uniqueNumbersCount--;
        }
    }

    std::cout << casesCount;

    return 0;
}