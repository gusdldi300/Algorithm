#include <iostream>
#include <vector>
#include <unordered_set>

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    unsigned int numbersCount;
    std::cin >> numbersCount;
    
    std::vector<unsigned int> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        numbers.push_back(number);
    }

    std::unordered_set<unsigned int> numberSet;
    
    unsigned long long casesCount = 0;

    unsigned int leftIndex = 0;
    unsigned int rightIndex = 0;

    while (rightIndex < numbersCount)
    {
        unsigned int checkNumber = numbers[rightIndex];
        
        if (numberSet.find(checkNumber) != numberSet.end())
        {
            casesCount += (rightIndex - leftIndex);
            numberSet.erase(numbers[leftIndex]);

            ++leftIndex;

            continue;
        }

        numberSet.insert(checkNumber);
        ++rightIndex;
    }

    for (leftIndex; leftIndex < numbersCount; ++leftIndex)
    {
        casesCount += (numbersCount - leftIndex);
    }

    std::cout << casesCount;

    return 0;
}