
#include <iostream>
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

    unsigned int count = 0;

    unsigned int leftIndex = 0;
    unsigned int rightIndex = 0;

    unsigned int sum = 0;
    while (rightIndex < numbersCount)
    {
        sum += numbers[rightIndex];
        ++rightIndex;

        while (sum >= targetSum)
        {
            if (sum == targetSum)
            {
                ++count;
            }

            sum -= numbers[leftIndex];
            ++leftIndex;
        }
    }

    std::cout << count;

    return 0;
}