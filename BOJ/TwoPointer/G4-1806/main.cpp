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

    unsigned int minLength = UINT_MAX;
    unsigned int continuousSum = 0;

    unsigned int endIndex = 0;

    for (unsigned int startIndex = 0; startIndex < numbers.size(); ++startIndex)
    {
        while (true)
        {
            if (continuousSum >= targetSum)
            {
                minLength = std::min(minLength, endIndex - startIndex);

                break;
            }

            if (endIndex >= numbers.size())
            {
                break;
            }

            continuousSum += numbers[endIndex];
            ++endIndex;
        }

        continuousSum -= numbers[startIndex];
    }

    std::cout << (minLength == UINT_MAX ? 0 : minLength);

    return 0;
}
