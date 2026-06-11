#include <iostream>
#include <climits>
#include <vector>

int main()
{
    unsigned int numbersCount;
    unsigned int targetSum;

    std::cin >> numbersCount >> targetSum;

    std::vector<unsigned int> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        numbers.push_back(number);
    }

    unsigned int minSumLength = UINT_MAX;
    unsigned int continuousSum = 0;

    unsigned int rightIndex = 0;
    for (unsigned int leftIndex = 0; leftIndex < numbersCount; ++leftIndex)
    {
        while (true)
        {
            if (continuousSum >= targetSum)
            {
                minSumLength = std::min(minSumLength, rightIndex - leftIndex);
                
                break;
            }

            if (rightIndex >= numbersCount)
            {
                break;
            }

            continuousSum += numbers[rightIndex];

            ++rightIndex;
        }

        continuousSum -= numbers[leftIndex];
    }
    
    std::cout << (minSumLength == UINT_MAX ? 0 : minSumLength);

    return 0;
}
