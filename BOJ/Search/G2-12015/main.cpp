#include <iostream>
#include <vector>

int main()
{
    unsigned int numbersCount;
    std::cin >> numbersCount;

    std::vector<unsigned int> numbers;
    for (unsigned int i = 0; i < numbersCount; ++i)
    {
        unsigned int number;
        std::cin >> number;

        numbers.push_back(number);
    }

    std::vector<unsigned int> ascendNumbers;
    ascendNumbers.push_back(numbers[0]);

    for (unsigned int i = 1; i < numbers.size(); ++i)
    {
        auto equalLowerIter = std::lower_bound(ascendNumbers.begin(), ascendNumbers.end(), numbers[i]);
        if (equalLowerIter == ascendNumbers.end())
        {
            ascendNumbers.push_back(numbers[i]);

            continue;
        }

        unsigned int replaceIndex = static_cast<unsigned int>(equalLowerIter - ascendNumbers.begin());
        ascendNumbers[replaceIndex] = numbers[i];
    }

    std::cout << ascendNumbers.size();

    return 0;
}