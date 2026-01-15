
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

struct NumberInfo
{
    unsigned int Number;
    unsigned int Count;
    unsigned int FirstIndex;
};

bool CompareNumberInfo(const NumberInfo& first, const NumberInfo& second)
{
    if (first.Count == second.Count)
    {
        return first.FirstIndex < second.FirstIndex;
    }

    return first.Count > second.Count;
}

int main()
{
    unsigned int numbersCount;
    unsigned int maxNumber;
    std::cin >> numbersCount >> maxNumber;

    std::vector<unsigned int> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        numbers.push_back(number);
    }

    std::unordered_map<unsigned int, std::pair<unsigned int, unsigned int>> numberCountsAndIndex;
    for (unsigned int numbersIndex = 0; numbersIndex < numbers.size(); ++numbersIndex)
    {
        unsigned int number = numbers[numbersIndex];
        if (numberCountsAndIndex.find(number) == numberCountsAndIndex.end())
        {
            std::pair<unsigned int, unsigned int> countsAndIndex;
            countsAndIndex.first = 1;
            countsAndIndex.second = numbersIndex;

            numberCountsAndIndex.insert(std::pair<unsigned int, std::pair<unsigned int, unsigned int>>(number, countsAndIndex));

            continue;
        }

        std::pair<unsigned int, unsigned int> countsAndIndex = numberCountsAndIndex[number];
        countsAndIndex.first++;
        
        numberCountsAndIndex[number] = countsAndIndex;
    }

    std::vector<NumberInfo> numberInfosOrdered;
    for (auto iter = numberCountsAndIndex.begin(); iter != numberCountsAndIndex.end(); ++iter)
    {
        NumberInfo numberInfo;
        numberInfo.Number = iter->first;
        numberInfo.Count = iter->second.first;
        numberInfo.FirstIndex = iter->second.second;

        numberInfosOrdered.push_back(numberInfo);
    }

    std::sort(numberInfosOrdered.begin(), numberInfosOrdered.end(), CompareNumberInfo);
    
    for (NumberInfo& numberInfo : numberInfosOrdered)
    {
        for (unsigned int i = 0; i < numberInfo.Count; ++i)
        {
            std::cout << numberInfo.Number << " ";
        }
    }

    return 0;
}